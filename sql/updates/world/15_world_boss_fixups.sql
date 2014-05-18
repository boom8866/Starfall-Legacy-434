-- Corborus Changes
REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(49642, 0, 0, 0, 395, 70); -- 5 Player Heroic

UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 20, `flags_extra`= 1 WHERE `entry`= 43438;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 49642;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (43438, 49642);

-- Slabhide Changes
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 20, `flags_extra`= 1, `mingold`= 17000, `maxgold`=18000 WHERE `entry`= 43214;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 35, `flags_extra`= 1, `mingold`= 17000, `maxgold`=18000 WHERE `entry`= 49538;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (43214, 49538);

-- Ozruk Changes
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 20, `flags_extra`= 1, `mingold`= 19000, `maxgold`=20000 WHERE `entry`= 42188;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 35, `flags_extra`= 1, `mingold`= 19000, `maxgold`=20000 WHERE `entry`= 49654;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (42188, 49654);

-- Baron Ashbury Changes
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 25, `maxdmg`= 45, `attackpower`= 7, `dmg_multiplier`= 25, `flags_extra`= 1 WHERE `entry`= 46962;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 495, `maxdmg`= 798, `attackpower`= 186, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 49708;
UPDATE `creature_template` SET `mechanic_immune_mask`= 0 | 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256 | 512 | 1024 | 2048 | 4096 | 8192 | 16384 | 65536 | 524288 | 4194304 | 8388608 | 67108864 WHERE `entry` IN (46962, 49708);

-- Baron Silverlaine
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 25, `maxdmg`= 45, `attackpower`= 15, `dmg_multiplier`= 25, `flags_extra`= 1 WHERE `entry`= 3887;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 399, `maxdmg`= 598, `attackpower`= 150, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 49709;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (3887, 49709);

-- Lord Walden
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 232, `maxdmg`= 398, `attackpower`= 9, `dmg_multiplier`= 5, `flags_extra`= 1 WHERE `entry`= 46963;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 495, `maxdmg`= 742, `attackpower`= 186, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 49711;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (46963, 49711);

-- Commander Springvale
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 25, `maxdmg`= 45, `attackpower`= 15, `dmg_multiplier`= 25, `flags_extra`= 1 WHERE `entry`= 4278;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 399, `maxdmg`= 598, `attackpower`= 150, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 49710;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (4278, 49710);

-- Lord Godfrey
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 25, `maxdmg`= 45, `attackpower`= 7, `dmg_multiplier`= 25, `flags_extra`= 1 WHERE `entry`= 46964;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 495, `maxdmg`= 798, `attackpower`= 186, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 49712;
UPDATE `creature_template` SET `mechanic_immune_mask`= 0 | 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256 | 512 | 1024 | 2048 | 4096 | 8192 | 16384 | 65536 | 524288 | 4194304 | 8388608 | 67108864 WHERE `entry` IN (46964, 49712);
