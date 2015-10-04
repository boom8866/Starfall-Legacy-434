/*
06/27/2012 20:07:12.448 -- last sniff timer

20:06:36.677 -- aggro
20:06:38.455 -- thrall teleport
20:06:42.090 -- assault aspects 1 18 37 155000

23:27:54.734 -- alextrasza conc


-------
23:31:05.212 -- i am deathwing
23:31:05.087 -- con
23:31:05.492 -- deathwing hp share npc engage
23:31:05.056 -- 
23:20:14.453 -- 
23:20:14.453 trigger aspec buffs

20:06:36.443 -- acestral recall
20:06:41.887 -- trigger aspect buffs

*/

UPDATE `creature_template` SET `scale`= 1 WHERE `entry`= 57693; -- Cosmetic Tentacle
DELETE FROM `vehicle_template_accessory` WHERE `accessory_entry`= 57693;
DELETE FROM `creature_template_addon` WHERE `entry` IN (56167, 56168, 56846, 106641, 106642, 106643, 106644);

-- Thrall
UPDATE `creature_template` SET `scriptname`= 'npc_thrall_madness' WHERE `entry`= 56103;
UPDATE `gossip_menu_option` SET `option_id`= 1, `npc_option_npcflag`= 1 WHERE `menu_id`= 13295; -- Thrall gossip

REPLACE INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(56103, 46598, 0, 0);
REPLACE INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(56103, 56694, 0, 1, "Thrall - wield The Dragon Soul", 8, 0);

-- Ysera
UPDATE `creature_template` SET `scriptname`= 'npc_ds_ysera_madness' WHERE `entry`= 56100;
-- Kalecgos
UPDATE `creature_template` SET `scriptname`= 'npc_ds_kalecgos_madness' WHERE `entry`= 56101;
-- Nozdormu
UPDATE `creature_template` SET `scriptname`= 'npc_ds_nozdormu_madness' WHERE `entry`= 56102;
-- Alexstrasza
UPDATE `creature_template` SET `scriptname`= 'npc_ds_alexstrasza_madness' WHERE `entry`= 56099;

-- Add trigger flag to several dummys
UPDATE `creature_template` SET `flags_extra`= 131, `InhabitType`= 4 WHERE `entry` IN (56699, 56307, 57882, 57378);
-- Mutated Corruption
UPDATE `creature_template` SET `scriptname`= 'npc_ds_mutated_corruption', `InhabitType`= 4, `exp`= 3, `Minlevel`= 88, `Maxlevel`= 88, `faction`= 14, `unit_flags2`= 134217728 WHERE `entry`= 56471;

-- Deathwing
UPDATE `creature_template` SET `scriptname`= 'boss_madness_of_deathwing', `unit_flags2`= 134250496 WHERE `entry`= 56173;
UPDATE `creature_template` SET `scriptname`= 'boss_tentacle' WHERE `entry` IN (56167, 56168, 56846);
UPDATE `creature_template` SET `InhabitType`= 4, `minlevel`= 87, `maxlevel`= 87, `faction`= 16, `exp`= 3 WHERE `entry`= 56262;
-- Deathwing Health Controller

-- Platform
UPDATE `creature_template` SET `scriptname`= 'npc_ds_platform' WHERE `entry`= 56307;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
-- Deathwing
(56173, 0, 0, 'You have done NOTHING. I will tear your world APART.', 14, 0, 100, 0, 0, 26527, 'Deathwing'),
(56173, 1, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s begins to cast |cFFFF0000|Hspell:107018|h[Assault Aspects]|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge'),
(56173, 2, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFF04FC32|Hspell:107018|hYsera|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 3, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFFFFFF00|Hspell:107018|hNozdormu|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 4, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFF5858FA|Hspell:107018|hKalecgos|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 5, 0, '|TInterface\\Icons\\ability_deathwing_assualtaspects.blp:20|t %s assaults |cFFFF0000|Hspell:107018|hAlextrasza|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Todesschwinge'),
(56173, 6, 0, '|TInterface\\Icons\\ability_deathwing_cataclysm.blp:20|t %s begins to cast |cFFFF0000|Hspell:106523|h [Cataclysm]|h|r! Stop him!', 41, 0, 100, 0, 0, 0, 'Todesschwinge'),
(56173, 7, 0, 'I AM DEATHWING! THE DESTROYER! THE END OF ALL THINGS! INEVITABLE! INDOMINABLE! I AM THE CATACLYSM!', 14, 0, 100, 0, 0, 26353, 'Todesschwinge to Schwingententakel'),
(56173, 8, 0, '|TInterface\\Icons\\inv_stave_2h_deathwingraiddw_d_01.blp:20|t %s falls torward, get to |cFF04FC32Ysera\'s|r platform!', 41, 0, 100, 0, 0, 0, 'Todesschwinge to Schwingententakel'),
(56173, 9, 0, '|TInterface\\Icons\\spell_fire_meteorstorm.blp:20|t %s begins to cast |cFFFF0000|Hspell:105651|h[Elementium Bolt]|h|r!', 41, 0, 100, 0, 0, 0, 'Todesschwinge'),
(56173, 10, 0, 'There\'s no shelter from my fury!.', 14, 0, 100, 0, 0, 26354, 'Todesschwinge'),
(56173, 10, 1, 'Your armor means nothing! Your faith - even less!', 14, 0, 100, 0, 0, 26355, 'Todesschwinge'),
(56173, 10, 2, 'The sea will swallow your smoldering remains!', 14, 0, 100, 0, 0, 26356, 'Todesschwinge'),
-- Ysera
(56100, 0, 0, 'I will bring you closer to the Emerald Dream. Seek safety there when the fight becomes too intense.', 14, 0, 100, 0, 0, 26142, 'Ysera - Assaulted'),
(56100, 1, 0, 'Deathwing is conjuring the final Cataclysm; even the Emerald Dream trembles. If we are to stop the spell, we must attack him together.', 14, 0, 100, 0, 0, 26144, 'Ysera - Cataclysm'),
-- Kalecgos
(56101, 0, 0, 'I will charge you with arcane energy to blast your foes.', 14, 0, 100, 0, 0, 26259, 'Kalecgos - Assaulted'),
(56101, 1, 0, 'The Destroyer is gathering all his might for a blow that will split the world. Attack him, now! We must stop the final Cataclysm!', 14, 0, 100, 0, 0, 26261, 'Kalecgos - Cataclysm'),
-- Nozdormu
(56102, 0, 0, 'I will slow the Destroyer''s attacks when I can.', 14, 0, 100, 0, 0, 25949, 'Nozdormu - Assaulted'),
(56102, 1, 0, 'Hurry, heroes. In mere moments Deathwing''s Cataclysm will complete what he begun and end the world. Join me in the attack, now!', 14, 0, 100, 0, 0, 25951, 'Nozdormu - Cataclysm'),
-- Alexstrasza
(56099, 0, 0, 'I will cleanse whatever corruption I can; my fire will not harm you.', 14, 0, 100, 0, 0, 26498, 'Alexstrasza - Assaulted'),
(56099, 1, 0, 'No! Such power! Deathwing''s summoning of the final Cataclysm will destroy all life on Azeroth. Quickly, we must interrupt him!', 14, 0, 100, 0, 0, 26500, 'Alexstrasza - Cataclysm');

DELETE FROM `creature` WHERE `id` IN (56846, 56167, 56168, 56844, 56173);

REPLACE INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(56844, 0, 0, 0x1, ''), -- Tail Tentacle
(56167, 0, 0, 0x1, ''), -- Arm Tentacle
(56846, 0, 0, 0x1, ''), -- Arm Tentacle
(56168, 0, 0, 0x1, ''); -- Wing Tentacle

UPDATE `creature_model_info` SET `combat_reach`= 15 WHERE `modelid`= 39405;

-- 106548
DELETE FROM conditions WHERE SourceEntry IN (106548, 106643, 106644, 106642, 106641, 105599, 109548, 109547, 106613, 109637, 109638, 109639, 106624, 109728, 109729, 109730, 106600,
109619, 109620, 109621, 106588, 109582, 109583, 109584);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 106548, 0, 0, 31, 0, 3, 56173, 0, 0, 0, '', 'Agonizing Pain - Target Deathwing'),
(13, 7, 109548, 0, 0, 31, 0, 3, 56173, 0, 0, 0, '', 'Share Health - Target Deathwing'),
(13, 7, 109547, 0, 0, 31, 0, 3, 57962, 0, 0, 0, '', 'Share Health Damage - Target Deathwing'),
(13, 7, 106643, 0, 0, 31, 0, 3, 57694, 0, 0, 0, '', 'Concentration - Target Right Arm'),
(13, 7, 106642, 0, 0, 31, 0, 3, 57686, 0, 0, 0, '', 'Concentration - Target Left Arm'),
(13, 7, 106644, 0, 0, 31, 0, 3, 57696, 0, 0, 0, '', 'Concentration - Target Right Wing'),
(13, 7, 105599, 0, 0, 31, 0, 3, 56262, 0, 0, 0, '', 'Elementium Bolt - Target Elementium Bolt'),
(13, 7, 106641, 0, 0, 31, 0, 3, 57695, 0, 0, 0, '', 'Concentration - Target Left Wing'),
(13, 7, 106613, 0, 0, 31, 0, 3, 56167, 0, 0, 0, '', 'Expose Weakness Ysera - Target Arm Tentacle'),
(13, 7, 109637, 0, 0, 31, 0, 3, 56167, 0, 0, 0, '', 'Expose Weakness Ysera - Target Arm Tentacle'),
(13, 7, 109638, 0, 0, 31, 0, 3, 56167, 0, 0, 0, '', 'Expose Weakness Ysera - Target Arm Tentacle'),
(13, 7, 109639, 0, 0, 31, 0, 3, 56167, 0, 0, 0, '', 'Expose Weakness Ysera - Target Arm Tentacle'),
(13, 7, 106624, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Kalecgos - Target Wing Tentacle'),
(13, 7, 109728, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Kalecgos - Target Wing Tentacle'),
(13, 7, 109729, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Kalecgos - Target Wing Tentacle'),
(13, 7, 109730, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Kalecgos - Target Wing Tentacle'),
(13, 7, 106600, 0, 0, 31, 0, 3, 56846, 0, 0, 0, '', 'Expose Weakness Nozdormu - Target Arm Tentacle'),
(13, 7, 109619, 0, 0, 31, 0, 3, 56846, 0, 0, 0, '', 'Expose Weakness Nozdormu - Target Arm Tentacle'),
(13, 7, 109620, 0, 0, 31, 0, 3, 56846, 0, 0, 0, '', 'Expose Weakness Nozdormu - Target Arm Tentacle'),
(13, 7, 109621, 0, 0, 31, 0, 3, 56846, 0, 0, 0, '', 'Expose Weakness Nozdormu - Target Arm Tentacle'),
(13, 7, 106588, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Alexstrasza - Target Wing Tentacle'),
(13, 7, 109582, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Alexstrasza - Target Wing Tentacle'),
(13, 7, 109583, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Alexstrasza - Target Wing Tentacle'),
(13, 7, 109584, 0, 0, 31, 0, 3, 56168, 0, 0, 0, '', 'Expose Weakness Alexstrasza - Target Wing Tentacle');


DELETE FROM `spell_script_names` WHERE spell_id IN (107018, 106644, 106643, 106642, 106641, 106664, 106673, 106672, 106548, 106382, 106940);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(107018, 'spell_ds_assault_aspects'),
(106644, 'spell_ds_concentration'),
(106643, 'spell_ds_concentration'),
(106642, 'spell_ds_concentration'),
(106641, 'spell_ds_concentration'),
(106673, 'spell_ds_carrying_winds_script'),
(106672, 'spell_ds_carrying_winds'),
(106548, 'spell_ds_agonizing_pain'),
(106382, 'spell_ds_crush_summon'),
(106940, 'spell_ds_trigger_concentration');


SET @ID := 5610100;
DELETE FROM `waypoint_data` WHERE `id` BETWEEN @ID+0 AND @ID+2;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Kalecgos
(@ID+0, 1, -12089.22, 12073.72, 57.31396),
(@ID+1, 2, -12042.77, 12021.11, 57.31396),
(@ID+2, 3, -12059.66, 11976.04, 57.31396);

SET @ID := 5609900;
DELETE FROM `waypoint_data` WHERE `id` BETWEEN @ID+0 AND @ID+2;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Alexstrasza
(@ID+0, 1, -11958.91, 12276.78, 54.98875),
(@ID+1, 2, -11911.33, 12205.85, 54.98875),
(@ID+2, 3, -11865.57, 12193.88, 54.98875);

SET @ID := 5610000;
DELETE FROM `waypoint_data` WHERE `id` BETWEEN @ID+0 AND @ID+2;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Ysera
(@ID+0, 1, -12108.63, 12175.13, 61.51709),
(@ID+1, 2, -12091.56, 12151.19, 61.51709),
(@ID+2, 3, -12088.4, 12130.21, 70.17785);

SET @ID := 5610200;
DELETE FROM `waypoint_data` WHERE `id` BETWEEN @ID+0 AND @ID+1;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Nozdormu
(@ID+0, 1, -12035.02, 12225.6, 62.73143),
(@ID+1, 2, -12021.92, 12179.42, 83.76831);


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
