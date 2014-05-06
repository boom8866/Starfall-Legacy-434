UPDATE `creature_template` SET `rank`= 3 WHERE `entry` IN (48936, 48940, 48941, 48943, 48944); -- Nhc
UPDATE `creature_template` SET `flags_extra`= flags_extra | 1, `rank`= 3 WHERE `entry` IN (48936, 48940, 48941, 48943, 48944, 49541); -- HC

-- Valor Points for Heroic Bosses
REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(48936, 0, 0, 0, 395, 70),
(48940, 0, 0, 0, 395, 70),
(48941, 0, 0, 0, 395, 70),
(48943, 0, 0, 0, 395, 70),
(48944, 0, 0, 0, 395, 70),
(49541, 0, 0, 0, 395, 70);
