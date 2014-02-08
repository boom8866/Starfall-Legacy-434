/*
06/27/2012 20:07:12.448 -- last sniff timer


20:06:36.677 -- aggro
20:06:38.455 -- thrall teleport
20:06:42.090 -- assault aspects 1 18 37 155000

20:06:51.918
20:06:52.402 -- tail tentacle target summon tail tentacle
20:06:58.080 -- summon crush target -- AnimKit.dbc Id: 1711 play -- tailtentacle too
20:07:03.587 -- casst impale 106400
20:07:38.952 -- impale 2
20:07:12.448 -- crush #1
20:08:37.141 -- cataclysm cast #1

20:09:04.457 -- pain #1
20:09:10.993 -- assault aspects #2
20:11:23.407 -- cataclysm #2

23:27:54.734 -- alextrasza conc


-------
23:31:05.212 -- i am deathwing
23:31:05.087 -- con
23:31:05.492 -- deathwing hp share npc engage
23:31:05.056 -- 
23:20:14.453 -- 
23:20:14.453 trigger aspec buffs

23:22:10.113 ... ysera
23:22:09.910 ... deathwing


23:20:09.461 -- aggro madness
23:20:55.435 -- elementium bolt
23:23:40.453
23:20:14.672
*/

UPDATE `creature_template` SET `scale`= 1 WHERE `entry`= 57693; -- Cosmetic Tentacle
DELETE FROM `vehicle_template_accessory` WHERE `accessory_entry`= 57693;

UPDATE `creature_template` SET `scriptname`= 'npc_thrall_madness' WHERE `entry`= 56103;
UPDATE `creature_template` SET `scriptname`= 'boss_madness_of_deathwing' WHERE `entry`= 56173;
UPDATE `creature_template` SET `scriptname`= 'boss_tentacle' WHERE `entry` IN (56167, 56168, 56846);
UPDATE `creature_template` SET `scriptname`= 'npc_ds_mutated_corruption', `InhabitType`= 4, `exp`= 3, `Minlevel`= 88, `Maxlevel`= 88 WHERE `entry`= 56471;
UPDATE `gossip_menu_option` SET `option_id`= 1, `npc_option_npcflag`= 1 WHERE `menu_id`= 13295; -- Thrall gossip
UPDATE `creature_template` SET `InhabitType`= 4, `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 56262;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(56173, 0, 0, 'You have done NOTHING. I will tear your world APART.', 14, 0, 100, 0, 0, 26527, 'Deathwing'),
(56173, 1, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s begins to cast |cFFFF0000|Hspell:107018|h[Assault Aspects]|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge'),
(56173, 2, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFF04FC32|Hspell:107018|hYsera|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 3, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFFFFFF00|Hspell:107018|hNozdormu|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 4, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFF5858FA|Hspell:107018|hKalcgos|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 5, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFFFF0000|Hspell:107018|hAlextrasza|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 6, 0, '|TInterface\\Icons\\ability_deathwing_cataclysm.blp:20|t %s begins to cast |cFFFF0000|Hspell:106523|h [Cataclysm]|h|r! Stop him!', 41, 0, 100, 0, 0, 0, 'Todesschwinge'),
(56173, 7, 0, 'I AM DEATHWING! THE DESTROYER! THE END OF ALL THINGS! INEVITABLE! INDOMINABLE! I AM THE CATACLYSM!', 14, 0, 100, 0, 0, 26353, 'Todesschwinge to Schwingententakel'),
(56173, 8, 0, '|TInterface\\Icons\\inv_stave_2h_deathwingraiddw_d_01.blp:20|t %s falls torward, get to |cFF04FC32Ysera\'s|r platform!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Schwingententakel'),
(56173, 9, 0, '|TInterface\\Icons\\spell_fire_meteorstorm.blp:20|t %s begins to cast |cFFFF0000|Hspell:105651|h[Elementium Bolt]|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge'),
(56173, 10, 0, 'There\'s no shelter from my fury!.', 14, 0, 100, 0, 0, 26354, 'Todesschwinge'),
(56173, 10, 1, 'Your armor means nothing! Your faith - even less!', 14, 0, 100, 0, 0, 26355, 'Todesschwinge'),
(56173, 10, 2, 'The sea will swallow your smoldering remains!', 14, 0, 100, 0, 0, 26356, 'Todesschwinge');

-- 26498

DELETE FROM `creature` WHERE `id` IN (56846, 56167, 56168, 56844, 56173);

REPLACE INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(56844, 0, 0, 0x1, ''), -- Tail Tentacle
(56167, 0, 0, 0x1, ''), -- Arm Tentacle
(56846, 0, 0, 0x1, ''), -- Arm Tentacle
(56168, 0, 0, 0x1, ''); -- Wing Tentacle

UPDATE `creature_model_info` SET `combat_reach`= 15 WHERE `modelid`= 39405;

-- 106548
DELETE FROM conditions WHERE SourceEntry IN (106548, 106643, 106644, 106642, 106641, 105599);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 106548, 0, 0, 31, 0, 3, 56173, 0, 0, 0, '', 'Agonizing Pain - Target Deathwing'),
(13, 7, 106643, 0, 0, 31, 0, 3, 57694, 0, 0, 0, '', 'Concentration - Target Right Arm'),
(13, 7, 106642, 0, 0, 31, 0, 3, 57686, 0, 0, 0, '', 'Concentration - Target Left Arm'),
(13, 7, 106644, 0, 0, 31, 0, 3, 57696, 0, 0, 0, '', 'Concentration - Target Right Wing'),
(13, 7, 105599, 0, 0, 31, 0, 3, 56262, 0, 0, 0, '', 'Elementium Bolt - Target Elementium Bolt'),
(13, 7, 106641, 0, 0, 31, 0, 3, 57695, 0, 0, 0, '', 'Concentration - Target Left Wing');


DELETE FROM `spell_script_names` WHERE spell_id IN (107018, 106644, 106643, 106642, 106641, 106664);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(107018, 'spell_ds_assault_aspects'),
(106644, 'spell_ds_concentration'),
(106643, 'spell_ds_concentration'),
(106642, 'spell_ds_concentration'),
(106641, 'spell_ds_concentration'),
(106664, 'spell_ds_carrying_winds');

SET @ID := 56101;
DELETE FROM `waypoint_data` WHERE `id` BETWEEN @ID+0 AND @ID+2;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Kalecgos
(@ID+0, 1, -12089.22, 12073.72, 57.31396),
(@ID+1, 2, -12042.77, 12021.11, 57.31396),
(@ID+2, 3, -12059.66, 11976.04, 57.31396);

SET @ID := 56099;
DELETE FROM `waypoint_data` WHERE `id` BETWEEN @ID+0 AND @ID+2;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Alexstrasza
(@ID+0, 1, -11958.91, 12276.78, 54.98875),
(@ID+1, 2, -11911.33, 12205.85, 54.98875),
(@ID+2, 3, -11865.57, 12193.88, 54.98875);

REPLACE INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(56100, 0, 0x3000000, 0x1, ''), -- Ysera
(56101, 0, 0x3000000, 0x1, ''), -- Kalecgos
(56102, 0, 0x3000000, 0x1, ''), -- Nozdormu
(56099, 0, 0x3000000, 0x1, ''); -- Alexstrasza


-- Areatriggers: 7320, 7319, 7318, 7317, 7316, 7315,  
-- death trigger: 7412
DELETE FROM `areatrigger_scripts` WHERE entry IN (7320, 7319, 7318, 7317, 7316, 7315, 7110, 7111, 7112, 7113, 7114, 7115);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(7315, 'at_ds_carrying_winds'),
(7316, 'at_ds_carrying_winds'),
(7317, 'at_ds_carrying_winds'),
(7318, 'at_ds_carrying_winds'),
(7319, 'at_ds_carrying_winds'),
(7320, 'at_ds_carrying_winds'),
(7110, 'at_ds_carrying_winds'),
(7111, 'at_ds_carrying_winds'),
(7112, 'at_ds_carrying_winds'),
(7113, 'at_ds_carrying_winds'),
(7114, 'at_ds_carrying_winds'),
(7115, 'at_ds_carrying_winds');
