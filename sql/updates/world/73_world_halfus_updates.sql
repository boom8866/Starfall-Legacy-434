-- Halfus Spikes Flags
UPDATE `creature_template` SET `unit_flags`= 33554432 WHERE `entry`= 44765;

-- Halfus Dragons Updates
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `IconName`= 'Interact', `faction_A`= 35, `faction_H`= 35, `exp`= 3, `AIName`= '', `mechanic_immune_mask`= 604708828 WHERE `entry` IN (44650, 46218, 46219, 46220, 44652, 46215, 46216, 46217, 44641, 46224, 46225, 46226, 44645, 46212, 46213, 46214, 44797, 46221, 46222, 46223);
UPDATE `creature_template` SET `difficulty_entry_3`= 46220 WHERE `entry`= 44650;
UPDATE `creature_template` SET `difficulty_entry_3`= 46217 WHERE `entry`= 44652;
UPDATE `creature_template` SET `difficulty_entry_3`= 46226 WHERE `entry`= 44641;
UPDATE `creature_template` SET `difficulty_entry_3`= 46214 WHERE `entry`= 44645;
UPDATE `creature_template` SET `difficulty_entry_3`= 46223 WHERE `entry`= 44797;

-- Proto Behemoth
UPDATE `creature_template` SET `difficulty_entry_3`= 46229 WHERE `entry`= 44687;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `InhabitType`= 4, `mechanic_immune_mask`= 604708828, `movementId`= 150 WHERE `entry` IN (44687, 46227, 46228, 46229);

-- Halfus Wyrmbreaker
UPDATE `creature_template` SET `mechanic_immune_mask`= 0 | 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256 | 512 | 1024 | 2048 | 4096 | 8192 | 16384 | 65536 | 524288 | 4194304 | 8388608 | 67108864, `baseattacktime` = 1500 WHERE `entry` IN (44600, 46209, 46210, 46211);
UPDATE `creature_template` SET `difficulty_entry_3`= 46211 WHERE `entry`= 44600;
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `rank`= 3, `exp`= 3, `flags_extra`= 1, `InhabitType`= 3, `faction_A`= 16, `faction_H`= 16 WHERE `entry` IN (44600, 46209, 46210, 46211);
