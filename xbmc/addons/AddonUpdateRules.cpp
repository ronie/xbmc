/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "AddonUpdateRules.h"

#include "AddonDatabase.h"
#include "threads/SingleLock.h"
#include "utils/log.h"

using namespace ADDON;

bool CAddonUpdateRules::RefreshRulesMap(const CAddonDatabase& db)
{
  m_updateRules.clear();
  db.GetAddonUpdateRules(m_updateRules);
  return true;
}

bool CAddonUpdateRules::IsAutoUpdateable(const std::string& id) const
{
  CSingleLock lock(m_critSection);
  return m_updateRules.find(id) == m_updateRules.end();
}

bool CAddonUpdateRules::IsUpdateableByRule(const std::string& id, AddonUpdateRule updateRule) const
{
  CSingleLock lock(m_critSection);
  const auto& updateRulesEntry = m_updateRules.find(id);
  return (updateRulesEntry == m_updateRules.end() ||
          std::none_of(updateRulesEntry->second.begin(), updateRulesEntry->second.end(),
                       [updateRule](AddonUpdateRule rule) { return rule == updateRule; }));
}

bool CAddonUpdateRules::AddRuleToList(CAddonDatabase& db,
                                      const std::string& id,
                                      AddonUpdateRule updateRule)
{
  CSingleLock lock(m_critSection);

  if (!IsUpdateableByRule(id, updateRule))
  {
    return true;
  }

  m_updateRules[id].emplace_back(updateRule);
  return db.SetUpdateRuleForAddon(id, updateRule);
}

bool CAddonUpdateRules::RemoveRuleFromList(CAddonDatabase& db,
                                           const std::string& id,
                                           AddonUpdateRule updateRule)
{
  return (updateRule != AddonUpdateRule::NONE && RemoveFromUpdateRuleslist(db, id, updateRule));
}

bool CAddonUpdateRules::RemoveAllRulesFromList(CAddonDatabase& db, const std::string& id)
{
  return RemoveFromUpdateRuleslist(db, id, AddonUpdateRule::NONE);
}

bool CAddonUpdateRules::RemoveFromUpdateRuleslist(CAddonDatabase& db,
                                                  const std::string& id,
                                                  AddonUpdateRule updateRule)
{
  CSingleLock lock(m_critSection);

  const auto& updateRulesEntry = m_updateRules.find(id);
  if (updateRulesEntry != m_updateRules.end())
  {
    bool onlySingleRule = (updateRulesEntry->second.size() == 1);

    if (updateRule == AddonUpdateRule::NONE ||
        (onlySingleRule && updateRulesEntry->second.front() == updateRule))
    {
      m_updateRules.erase(id);
      db.RemoveAllUpdateRulesForAddon(id);
      return true;
    }
    else if (!onlySingleRule)
    {
      const auto& position =
          std::find(updateRulesEntry->second.begin(), updateRulesEntry->second.end(), updateRule);
      if (position != updateRulesEntry->second.end())
      {
        updateRulesEntry->second.erase(position);
        db.RemoveUpdateRuleForAddon(id, updateRule);
      }
      return true;
    }
  }
  return false;
}
