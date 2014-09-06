DELETE FROM `creature` WHERE `id`= '30337';
DELETE FROM `creature_template` WHERE `entry` IN (144959, 30337);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(144959, 0, 0, 0, 0, 0, 26757, 0, 0, 0, 'Jotunheim Rapid-Fire Harpoon', NULL, 'vehichleCursor', 0, 80, 80, 2, 0, 35, 35, 16777216, 0.0001, 0.0001, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 4, 0, 2048, 8, 0, 0, 0, 0, 0, 0, 0, 9, 1048576, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5685, 0, 56570, 0, 0, 0, 0, 0, 0, 229, 0, 0, '', 0, 5, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 16384, 0, 'npc_generic_harpoon_cannon', 15595);

SET @CGUID := 840927;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+14;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 144959, 571, 1, 1, 0, 0, 8407.96, 3429.16, 627.003, 1.06465, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+1, 144959, 571, 1, 1, 0, 0, 8417.64, 3422.16, 626.643, 0.925025, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+2, 144959, 571, 1, 1, 0, 0, 8401.15, 3437.11, 626.739, 0.767945, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+3, 144959, 571, 1, 1, 0, 0, 8413.56, 3426.17, 626.777, 1.13446, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+4, 144959, 571, 1, 1, 0, 0, 8395.42, 3441.92, 626.013, 0.959931, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+5, 144959, 571, 1, 1, 0, 0, 8391.8, 3444.84, 625.532, 1.15192, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+6, 144959, 571, 1, 1, 0, 0, 8426.32, 3385.19, 626.718, 0.139626, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+7, 144959, 571, 1, 1, 0, 0, 8426.68, 3373.28, 625.554, 6.07375, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+8, 144959, 571, 1, 1, 0, 0, 8424.97, 3401.85, 626.807, 6.14356, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+9, 144959, 571, 1, 1, 0, 0, 8424.28, 3396.04, 627.184, 6.19592, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+10, 144959, 571, 1, 1, 0, 0, 8426.63, 3378.09, 626.08, 0.0174533, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+11, 144959, 571, 1, 1, 0, 0, 8027.71, 3696.45, 617.48, 1.69297, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+12, 144959, 571, 1, 1, 0, 0, 8004.31, 3698.89, 615.863, 1.88496, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+13, 144959, 571, 1, 1, 0, 0, 8010.09, 3699.28, 616.451, 1.46608, 300, 0, 0, 12600, 100, 0, 0, 0, 0),
(@CGUID+14, 144959, 571, 1, 1, 0, 0, 8017.63, 3698.49, 617.179, 1.29154, 300, 0, 0, 12600, 100, 0, 0, 0, 0);