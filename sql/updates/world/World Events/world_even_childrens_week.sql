UPDATE `creature` SET `id`=51988 WHERE `guid`=31254;
UPDATE `creature` SET `id`=51989 WHERE `guid`=161970;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (732529, 738912);
UPDATE `quest_template` SET `RequiredRaces`=946 WHERE `Id` IN (10942, 172);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=2 WHERE `item`=43507 AND `ChanceOrQuestChance` < 1;
UPDATE `creature_loot_template` SET `groupid`=2 WHERE `item`=43507;
UPDATE `item_loot_template` SET `groupid`=1 WHERE `entry`=44113 AND `item`=33925;
UPDATE `quest_template` SET `RewardItemId1`=46545, `RewardItemCount1`=1 WHERE `Id`=13959;
UPDATE `quest_template` SET `RewardItemId1`=46544, `RewardItemCount1`=1 WHERE `Id`=13960;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738913;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=729174;

DELETE FROM `game_event_creature` WHERE `guid` = '738913';
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(10, 738913);

DELETE FROM `game_event_gameobject` WHERE `guid` = '729874';
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(10, 729874);

UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=12761 AND `id`=0;

DELETE FROM `npc_vendor` WHERE `entry` = '52358';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`) VALUES
(52358, 0, 34498, 0, 0, 0, 1),
(52358, 0, 44481, 0, 0, 0, 1),
(52358, 0, 44482, 0, 0, 0, 1),
(52358, 0, 44599, 0, 0, 0, 1),
(52358, 0, 44601, 0, 0, 0, 1),
(52358, 0, 44606, 0, 0, 0, 1),
(52358, 0, 45057, 0, 0, 0, 1),
(52358, 0, 46725, 0, 0, 0, 1),
(52358, 0, 48601, 0, 0, 0, 1),
(52358, 0, 54343, 0, 0, 0, 1),
(52358, 0, 54436, 0, 0, 0, 1),
(52358, 0, 54437, 0, 0, 0, 1),
(52358, 0, 54438, 0, 0, 0, 1),
(52358, 0, 68890, 0, 0, 0, 1),
(52358, 0, 69057, 0, 0, 0, 1);

DELETE FROM `npc_vendor` WHERE `item` = '69057';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`) VALUES
(52358, 0, 69057, 0, 0, 0, 1),
(52809, 0, 69057, 0, 0, 0, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (23012, 23013);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(23012, 'spell_cw_summon_orphan'),
(23013, 'spell_cw_summon_orphan');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=52585 AND `spell_id`=90105;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=52585;
UPDATE `creature_template` SET `unit_flags`=768, `InhabitType`=3, `ScriptName`='npc_cw_redhound_twoseater_trigger' WHERE `entry`=52585;
UPDATE `creature_template` SET `minlevel`=5, `maxlevel`=5, `unit_flags`=768, `VehicleId`=1577, `InhabitType`=4, `ScriptName`='npc_vw_redhound_twoseater_vehicle' WHERE `entry`=52583;

DELETE FROM `script_waypoint` WHERE `entry` = '52583';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(52583, 1, 2655.08, -6138.38, 131.92, 'Redhound Two-Seater (CW)'),
(52583, 2, 2646.82, -6110.06, 123.04, 'Redhound Two-Seater (CW)'),
(52583, 3, 2636.78, -6062.60, 100.38, 'Redhound Two-Seater (CW)'),
(52583, 4, 2629.27, -6009.33, 100.48, 'Redhound Two-Seater (CW)'),
(52583, 5, 2684.69, -5880.80, 97.14, 'Redhound Two-Seater (CW)'),
(52583, 6, 2706.82, -5847.92, 98.26, 'Redhound Two-Seater (CW)'),
(52583, 7, 2780.98, -5770.83, 111.83, 'Redhound Two-Seater (CW)'),
(52583, 8, 2802.95, -5733.89, 123.47, 'Redhound Two-Seater (CW)'),
(52583, 9, 2806.83, -5727.36, 125.16, 'Redhound Two-Seater (CW)'),
(52583, 10, 2824.59, -5686.51, 127.83, 'Redhound Two-Seater (CW)'),
(52583, 11, 2830.56, -5642.52, 127.36, 'Redhound Two-Seater (CW)'),
(52583, 12, 2840.71, -5529.31, 134.45, 'Redhound Two-Seater (CW)'),
(52583, 13, 2836.16, -5466.06, 143.58, 'Redhound Two-Seater (CW)'),
(52583, 14, 2840.19, -5418.35, 141.40, 'Redhound Two-Seater (CW)'),
(52583, 15, 2858.93, -5380.91, 132.63, 'Redhound Two-Seater (CW)'),
(52583, 16, 2904.34, -5310.00, 129.12, 'Redhound Two-Seater (CW)'),
(52583, 17, 2909.12, -5263.02, 134.93, 'Redhound Two-Seater (CW)'),
(52583, 18, 2908.08, -5223.09, 129.86, 'Redhound Two-Seater (CW)'),
(52583, 19, 2926.11, -5129.59, 131.76, 'Redhound Two-Seater (CW)'),
(52583, 20, 2930.41, -5065.10, 165.60, 'Redhound Two-Seater (CW)'),
(52583, 21, 2969.12, -4951.13, 166.10, 'Redhound Two-Seater (CW)'),
(52583, 22, 2985.53, -4930.43, 163.99, 'Redhound Two-Seater (CW)'),
(52583, 23, 3002.53, -4909.65, 162.17, 'Redhound Two-Seater (CW)'),
(52583, 24, 3022.45, -4880.55, 162.17, 'Redhound Two-Seater (CW)'),
(52583, 25, 3047.28, -4874.44, 142.96, 'Redhound Two-Seater (CW)'),
(52583, 26, 3130.56, -4933.71, 144.99, 'Redhound Two-Seater (CW)'),
(52583, 27, 3166.46, -4901.59, 144.99, 'Redhound Two-Seater (CW)'),
(52583, 28, 3165.47, -4774.27, 170.64, 'Redhound Two-Seater (CW)'),
(52583, 29, 3097.51, -4787.22, 170.61, 'Redhound Two-Seater (CW)'),
(52583, 30, 3094.41, -4825.83, 170.61, 'Redhound Two-Seater (CW)'),
(52583, 31, 3119.27, -4789.89, 170.61, 'Redhound Two-Seater (CW)'),
(52583, 32, 3014.86, -4805.83, 156.02, 'Redhound Two-Seater (CW)'),
(52583, 33, 3022.45, -4845.50, 156.56, 'Redhound Two-Seater (CW)'),
(52583, 34, 3042.77, -4848.20, 142.08, 'Redhound Two-Seater (CW)'),
(52583, 35, 3042.77, -4848.20, 126.44, 'Redhound Two-Seater (CW)'),
(52583, 36, 3077.72, -4850.58, 149.95, 'Redhound Two-Seater (CW)'),
(52583, 37, 3101.51, -4852.77, 143.87, 'Redhound Two-Seater (CW)'),
(52583, 38, 3185.97, -4839.00, 168.80, 'Redhound Two-Seater (CW)'),
(52583, 39, 3409.25, -4812.11, 153.66, 'Redhound Two-Seater (CW)'),
(52583, 40, 3501.25, -4793.60, 159.12, 'Redhound Two-Seater (CW)'),
(52583, 41, 3613.21, -4794.11, 157.88, 'Redhound Two-Seater (CW)');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738914;

DELETE FROM `creature_text` WHERE `entry`=14444;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(14444,0,0,'This is gonna be fun!',12,0,100,0,0,0,'Comment'),
(14444,1,0,'I\'ve seen goblins riding this things. I know they can go faster!',12,0,100,0,0,0,'Comment'),
(14444,2,0,'I wonder what this button does...',12,0,100,0,0,0,'Comment'),
(14444,3,0,'Now THAT\'s more like it!',12,0,100,0,0,0,'Comment'),
(14444,4,0,'I\'ve figured out how this works. I\'m taking control!',12,0,100,0,0,0,'Comment'),
(14444,5,0,'Hang on onto your, um... helmet!',12,0,100,0,0,0,'Comment'),
(14444,6,0,'I\'m loosing control!',12,0,100,0,0,0,'Comment'),
(14444,7,0,'No, rocket! Don\'t go that way!',12,0,100,0,0,0,'Comment'),
(14444,8,0,'I think I found the emergency button. Rockets have those, don\'t they?',12,0,100,0,0,0,'Comment'),
(14444,9,0,'I did it! I Got us back to the track!',12,0,100,0,0,0,'Comment'),
(14444,10,0,'This is the only button I haven\'t pushed yet. Let\'s give it a try!',12,0,100,0,0,0,'Comment'),
(14444,11,0,'Whooooooooooa!',12,0,100,0,0,0,'Comment');