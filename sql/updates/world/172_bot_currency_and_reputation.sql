-- 25 player bosses: 45 Valor Points
UPDATE `creature_onkill_reward` SET `CurrencyCount1`= 45 WHERE `creature_id` IN (46209, 49897);

-- 195 guild reputation to all fixed BoT bosses
UPDATE `creature_onkill_reward` SET `RewOnKillRepFaction1`= 1168, `RewOnKillRepValue1`= 195, `MaxStanding1`= 7 WHERE `creature_id` IN (46209, 49897, 44600, 45992);

REPLACE INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepValue1`, `MaxStanding1`) VALUES
(43735, 396, 35, 1168, 195, 7), -- Elementium Monstrosity 10 player normal + 195 Guild Reputation
(49619, 396, 45, 1168, 195, 7); -- Elementium Monstrosity 25 player normal + 195 Guild Reputation
