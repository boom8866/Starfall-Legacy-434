
/*
Author : Northstrider
Descr. : Ragnaros Encounter
Ticket :
*/
-- Set Spawnmask for 10 Player and 10 Player HC
UPDATE `creature` SET `spawnMask`= 5 WHERE `map`= 720;
UPDATE `gameobject` SET `spawnMask`= 5 WHERE `map`= 720;
-- Cleanup unneeded spawns
DELETE FROM `creature` WHERE `id` IN (53086, 53485, 53140, 53231, 52409, 53266, 53393, 53420, 53393, 53872, 53875, 53876);
-- Add trigger flags to trigger Npc's
UPDATE `creature_template` SET `flags_extra`= 130 WHERE `entry` IN (53268, 53266, 53363, 53268, 53420, 53393, 53485, 53473, 53186);
-- Scriptname for Areatrigger Script
DELETE FROM `areatrigger_scripts` WHERE entry = 6845;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6845, 'at_sulfuron_keep');
-- Template Updates
UPDATE `creature_template` SET `scriptname`= 'boss_ragnaros_cata' WHERE `entry`= 52409;
UPDATE `creature_template` SET `scriptname`= 'npc_fl_archdruids' WHERE `entry` IN (53872, 53875, 53876);
UPDATE `creature_template` SET `exp`= 3, `minlevel`= 88, `maxlevel`= 88, `faction_A`= 2234, `faction_H`= 2234 WHERE `entry` =53798;
UPDATE `creature_template` SET `scriptname`= 'npc_magma_trap' WHERE `entry`= 53086;
UPDATE `creature_template` SET `InhabitType`= 4, `scriptname`= 'npc_fl_lava_wave' WHERE `entry`= 53363;
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry`= 53186;
UPDATE `creature_template` SET `scriptname`= 'npc_sulfuras_smash' WHERE `entry`= 53268;
UPDATE `creature_template` SET `scriptname`= 'npc_sulfuras_hammer' WHERE `entry`= 53420;
UPDATE `creature_template` SET `difficulty_entry_2`= 53801, `scriptname`= 'npc_son_of_flame' WHERE `entry`= 53140;
UPDATE `creature_template` SET `speed_walk`= 1, `speed_run`= 1.71429 WHERE `entry`= 53801;
UPDATE `creature_template` SET `exp`= 3, `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16 WHERE `entry` IN (53801, 53811, 53817, 53814);
UPDATE `creature_template` SET `scriptname`= 'npc_engulfing_flame' WHERE `entry`= 53485;
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `InhabitType`= 4 WHERE `entry` IN (52409, 53797, 53798);
UPDATE `creature_template` SET `difficulty_entry_2`= 53811, `minlevel`= 87, `maxlevel`= 87, `exp`= 3, `faction_A`= 16, `faction_H`= 16, `scriptname`= 'npc_fl_molten_elemental' WHERE `entry`= 53189;
UPDATE `creature_template` SET `difficulty_entry_2`= 53817, `scriptname`= 'npc_fl_lava_scion' WHERE `entry`= 53231;
UPDATE `creature_template` SET `faction_A`= 16, `faction_H`= 16, `scriptname`= 'npc_fl_blazing_heat' WHERE `entry`= 53473;
UPDATE `creature_template` SET `difficulty_entry_2`= 53814, `faction_A`= 16, `faction_H`= 16, `minlevel`= 87, `maxlevel`= 87, `exp`= 3, `scriptname`= 'npc_fl_living_meteor' WHERE `entry`= 53500;
-- Spell Script Names
DELETE FROM `spell_script_names` WHERE spell_id IN (99012, 99054, 99126, 100985, 100171);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(99012, 'spell_fl_splitting_blow'),
(99054, 'spell_fl_invoke_sons'),
(99126, 'spell_fl_blazing_heat'),
(100985, 'spell_fl_blazing_heat'),
(100171, 'spell_fl_world_in_flames');
-- Encounter Texts
DELETE FROM `creature_text` WHERE entry IN (52409, 53875, 53872);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(52409, 0, 0, 'Mortal Insects You dare tresspass into MY domain? Your arrogance will be purged in living flame.', 14, 0, 100, 0, 0, 24517, 'Ragnaros - Intro'),
(52409, 1, 0, 'Too soon... You have come too soon...', 14, 0, 100, 0, 0, 24519, 'Ragnaros - Death Normal Mode'),
(52409, 2, 0, 'Not... No', 14, 0, 100, 0, 0, 24518, 'Ragnaros - Death Heroic Mode'),
(52409, 3, 0, 'This is MY realm', 14, 0, 100, 0, 0, 24529, 'Ragnaros - Kill 1'),
(52409, 3, 1, 'Pathetic.', 14, 0, 100, 0, 0, 24530, 'Ragnaros - Kill 2'),
(52409, 3, 2, 'Die, insect', 14, 0, 100, 0, 0, 24531, 'Ragnaros - Kill 3'),
(52409, 4, 0, '|TInterface\\Icons\\spell_fire_ragnaros_splittingblow.blp:20|t%s begins to cast |cFFFF0000|Hspell:98951|h''Splitting Blow''|h|r ', 41, 0, 100, 0, 0, 24520, 'Ragnaros - Announce Splitting Blow'),
(52409, 5, 0, 'You will be destroyed', 14, 0, 100, 0, 0, 24520, 'Ragnaros - Hammer Drop 1'),
(52409, 5, 1, 'Die', 14, 0, 100, 0, 0, 24521, 'Ragnaros - Hammer Drop 2'),
(52409, 5, 2, 'Your judgement has come', 14, 0, 100, 0, 0, 24522, 'Ragnaros - Hammer Drop 3'),
(52409, 6, 0, 'Enough I will finish this.', 14, 0, 100, 0, 0, 24523, 'Ragnaros - Hammer Pickup 1'),
(52409, 6, 1, 'Fall to your knees, mortals This ends now.', 14, 0, 100, 0, 0, 24524, 'Ragnaros - Hammer Pickup 2'),
(52409, 6, 2, 'Sulfuras will be your end.', 14, 0, 100, 0, 0, 24525, 'Ragnaros - Hammer Pickup 3'),
(52409, 7, 0, 'Come forth, my servants', 14, 0, 100, 0, 0, 24513, 'Ragnaros - Sons of Flame 1'),
(52409, 7, 1, 'Minions of fire', 14, 0, 100, 0, 0, 24514, 'Ragnaros - Sons of Flame 2'),
(52409, 7, 2, 'Denizens of flame, come to me', 14, 0, 100, 0, 0, 24515, 'Ragnaros - Sons of Flame 3'),
(52409, 7, 3, 'Arise, servants of fire, consume their flesh', 14, 0, 100, 0, 0, 24516, 'Ragnaros - Sons of Flame 4'),
(52409, 8, 0, '%s prepares to |cFFFF0000emerge|r', 41, 0, 100, 0, 0, 0, 'Ragnaros - Announce Emerge'),
(52409, 9, 0, '|TInterface\\Icons\\spell_fire_selfdestruct.blp:20|t%s casts |cFFFF6600|Hspell:98164|h''Magma Trap''|h|r', 41, 0, 100, 0, 0, 0, 'Ragnaros - Magma Trap'),
(52409, 10, 0, '|TInterface\\Icons\\spell_shaman_lavasurge.blp:20|t%s casts |cFFFF0000|Hspell:98710|h''Sulfuras Smash''|h|r ', 41, 0, 100, 0, 0, 0, 'Ragnaros - Sulfuras Smash'),
(52409, 11, 0, 'Too soon…', 14, 0, 100, 0, 0, 24528, 'Ragnaros - Flee Heroic'),
(52409, 12, 0, 'Arrggh, outsiders - this is not your realm', 14, 0, 100, 0, 0, 24527, 'Ragnaros - Not Your Realm'),
(52409, 13, 0, 'When I finish this, your pathetic mortal world will burn with my vengeance', 14, 0, 100, 0, 0, 24526, 'Ragnaros - Standup'),
(53875, 0, 0, 'Heroes', 14, 0, 100, 0, 0, 25169, 'Malfurion - Talk'),
(53872, 0, 0, 'No, fiend. Your time is NOW.', 14, 0, 100, 0, 0, 25159, 'Cenarius - Taunt Ragnaros');
-- Conditions for some spell targets
DELETE FROM conditions WHERE SourceEntry IN (98710, 98953, 98952, 98951, 99056, 99050, 99172, 99235, 99236, 99054, 99012, 99216, 99217, 99218, 99125, 100344, 100342, 100345, 100907, 100891, 100884, 100878, 100881, 100176, 100179, 100182);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 98710, 0, 0, 31, 0, 3, 53268, 0, 0, 0, '', 'Sulfuras Smash - Target Dummy'),
(13, 1, 100891, 0, 0, 31, 0, 3, 53268, 0, 0, 0, '', 'Sulfuras Smash - Target Dummy'),
(13, 1, 98951, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 98952, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 98953, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 100884, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 100878, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 100881, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 99012, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow Trigger Missile - Target Dummy'),
(13, 1, 99054, 0, 0, 31, 0, 3, 53140, 0, 0, 0, '', 'Invoke Sons - Target Son of Flame'),
(13, 1, 99216, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Melee Visual'),
(13, 1, 99172, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Melee Damage'),
(13, 1, 99217, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Center Visual'),
(13, 1, 99235, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Center Damage'),
(13, 1, 99218, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Range Visual'),
(13, 1, 99236, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Range Damage'),
(13, 1, 100176, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Melee Damage'),
(13, 1, 100179, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Center Damage'),
(13, 1, 100182, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Range Damage'),
(13, 1, 99125, 0, 0, 31, 0, 3, 53473, 0, 0, 0, '', 'Blazing Heat - Target Dummy'),
(13, 1, 100344, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Hamuul Draw Firelord - Target Ragnaros'),
(13, 1, 100342, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Malfurion Draw Firelord - Target Ragnaros'),
(13, 1, 100345, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Cenarius Draw Firelord - Target Ragnaros'),
(13, 1, 100907, 0, 0, 31, 0, 3, 53500, 0, 0, 0, '', 'Freeze Meteors - Target Living Meteors');
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(53801, 0, 0, 0, 1, 0, '21857 19818');
-- Linked spells for Molten Seed to supress code size
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-98520, -100888);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
('-98520', '-100153', '0', 'Molten Elemental - Remove Invisibility'),
('-98520', '98518', '0', 'Molten Elemental - Cast Molten Inferno'),
('-98520', '100157', '0', 'Molten Elemental - Cast Molten Aura'),
('-100888', '-100153', '0', 'Molten Elemental - Remove Invisibility'),
('-100888', '100253', '0', 'Molten Elemental - Cast Molten Inferno'),
('-100888', '100157', '0', 'Molten Elemental - Cast Molten Aura');
﻿
/*
Author : Northstrider
Descr. : deadmines spawns and addons and basic template updates
Ticket : 
*/
DELETE FROM `creature` WHERE `map`= 36 AND `id` NOT IN (4);
DELETE FROM `gameobject` WHERE `map`= 36;
DELETE FROM `creature_addon` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);
SET @CGUID := 782360;
SET @OGUID := 778924;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+41;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+0, 208516, 36, 1, 1, -14.75671, -389.0967, 63.59012, 1.553341, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+1, 208515, 36, 1, 1, -14.75671, -389.0967, 63.59012, 1.553341, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+2, 208002, 36, 1, 1, -64.15278, -385.9896, 53.19195, 1.850049, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+3, 13965, 36, 1, 1, -191.4146, -457.4458, 54.43914, 1.692966, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Factory Door (Area: 0)
(@OGUID+4, 16399, 36, 1, 1, -168.514, -579.8608, 19.31593, 3.124123, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Foundry Door (Area: 0)
(@OGUID+5, 17153, 36, 1, 1, -262.7137, -482.3611, 49.43531, 6.265733, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Heavy Door (Area: 0)
(@OGUID+6, 208002, 36, 1, 1, -201.0955, -606.0504, 19.3022, 2.740162, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+7, 17154, 36, 1, 1, -242.9652, -578.561, 51.1366, 3.124123, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Heavy Door (Area: 0)
(@OGUID+8, 16397, 36, 1, 1, -100.5015, -668.7706, 7.410492, 1.815142, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Iron Clad Door (Area: 0)
(@OGUID+9, 208002, 36, 1, 1, -305.3212, -491.2917, 49.232, 0.4886912, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+10, 16400, 36, 1, 1, -290.2941, -536.9603, 49.43531, 1.553341, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Mast Room Door (Area: 0)
(@OGUID+11, 208002, 36, 1, 1, -129.9149, -788.8976, 17.34092, 0.3665176, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+12, 207079, 36, 1, 1, -197.436, -490.266, 53.8617, 4.380776, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+13, 207079, 36, 1, 1, -179.665, -492.655, 54.3416, 0, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+14, 207079, 36, 1, 1, -192.778, -505.63, 53.1919, 3.036838, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+15, 207079, 36, 1, 1, -182.196, -502.55, 53.5372, 2.967041, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+16, 207079, 36, 1, 1, -221.563, -485.286, 48.9329, 5.009095, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+17, 207079, 36, 1, 1, -205.415, -502.424, 52.0631, 6.178466, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+18, 207079, 36, 1, 1, -158.422, -508.253, 53.4218, 0, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+19, 207079, 36, 1, 1, -236.092, -488.552, 49.4053, 3.001947, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+20, 207079, 36, 1, 1, -219.762, -504.585, 50.4594, 0, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+21, 207079, 36, 1, 1, -169.604, -509.63, 53.5638, 5.061456, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+22, 207079, 36, 1, 1, -210.984, -511.063, 50.8982, 3.281239, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+23, 207079, 36, 1, 1, -156.175, -520.281, 52.3784, 2.042035, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+24, 207079, 36, 1, 1, -150.311, -519.649, 52.8737, 0.6981315, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+25, 207079, 36, 1, 1, -158.554, -530.83, 52.3817, 1.221729, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+26, 207079, 36, 1, 1, -154.227, -529.694, 49.7548, 4.01426, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+27, 207079, 36, 1, 1, -149.149, -532.719, 49.8969, 5.009095, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+28, 207290, 36, 1, 1, -205.1858, -544.9375, 54.5354, 4.71239, 0, 0, 0, 1, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+29, 123207, 36, 1, 1, -205.6642, -574.5812, 20.99874, 1.553341, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Goblin Smelting Pot (Area: 0)
(@OGUID+30, 123209, 36, 1, 1, -201.0433, -579.3741, 20.99874, 6.265733, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Goblin Smelting Pot (Area: 0)
(@OGUID+31, 123208, 36, 1, 1, -210.4285, -579.2006, 20.99874, 3.124123, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Goblin Smelting Pot (Area: 0)
(@OGUID+32, 123210, 36, 1, 1, -205.8048, -583.9644, 20.99874, 4.694937, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Goblin Smelting Pot (Area: 0)
(@OGUID+33, 101834, 36, 1, 1, -165.4043, -576.9242, 19.30644, 3.298687, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Door Lever (Area: 0)
(@OGUID+34, 101831, 36, 1, 1, -188.1366, -460.3134, 54.55907, 1.727875, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Door Lever (Area: 0)
(@OGUID+35, 123211, 36, 1, 1, -205.9727, -613.2621, 19.40043, 6.178468, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Foundry Anvil (Area: 0)
(@OGUID+36, 123212, 36, 1, 1, -196.4172, -610.9805, 19.40043, 4.258607, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Foundry Anvil (Area: 0)
(@OGUID+37, 123213, 36, 1, 1, -196.4913, -605.381, 19.40043, 1.640607, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Foundry Anvil (Area: 0)
(@OGUID+38, 16398, 36, 1, 1, -107.5617, -659.6737, 7.212111, 5.392893, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Defias Cannon (Area: 0)
(@OGUID+39, 101833, 36, 1, 1, -96.92775, -670.5967, 7.403381, 1.902409, 0, 0, 0.7009094, 0.7132503, 7200, 255, 1), -- Door Lever (Area: 0)
(@OGUID+40, 208520, 36, 1, 1, -109.4304, -1003.769, 33.60406, 1.292679, 0, 0, 0.8849877, 0.4656144, 7200, 255, 1), -- -Unknown- (Area: 0)
(@OGUID+41, 208519, 36, 1, 1, -109.4304, -1003.769, 33.60406, 1.292679, 0, 0, 0.8849877, 0.4656144, 7200, 255, 1); -- -Unknown- (Area: 0)
UPDATE `creature_template` SET `modelid1`=169 WHERE `entry`=53488; -- Summon Enabler Stalker
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=49042; -- Glubtok Firewall Platter Creature Level 2c
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=49040; -- Glubtok Firewall Platter Creature Level 1c
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=48974; -- Glubtok Firewall Platter
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=48975; -- Glubtok Firewall Platter Creature Level 1a
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=48976; -- Glubtok Firewall Platter Creature Level 2a
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=49039; -- Glubtok Firewall Platter Creature Level 1b
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=49041; -- Glubtok Firewall Platter Creature Level 2b
UPDATE `creature_template` SET `gossip_menu_id`=12505, `npcflag`=1 WHERE `entry`=49564; -- A Note From Vanessa
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857, `exp`=3 WHERE `entry`=49429; -- Vanessa VanCleef
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49454; -- Vanessa's Trap Bunny
UPDATE `creature_template` SET `npcflag`=16777216 WHERE `entry`=49457; -- Steam Valve
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=51594; -- Glubtok Nightmare Fire Bunny
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49671; -- Vanessa VanCleef
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49670; -- Glubtok
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49674; -- Helix Gearbreaker
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49493; -- Nightmare Skitterling
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.190476 WHERE `entry`=49495; -- Chattering Horror
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.190476 WHERE `entry`=49494; -- Darkweb Devourer
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49681; -- Foe Reaper 5000
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=49520; -- Vanessa Lightning Platter
UPDATE `creature_template` SET `speed_walk`=0.2, `speed_run`=1.142857 WHERE `entry`=49521; -- Vanessa Lightning Stalker
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49682; -- Ripsnarl
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49534; -- Emme Harrington
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49532; -- Enraged Worgen
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857, `exp`=3 WHERE `entry`=49139; -- Helix' Crew
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857, `exp`=3 WHERE `entry`=49138; -- Helix' Crew
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857, `exp`=3 WHERE `entry`=49136; -- Helix' Crew
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857, `exp`=3 WHERE `entry`=49137; -- Helix' Crew
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=0.8571429 WHERE `entry`=51462; -- Mine Rat
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49552; -- Vanessa's Rope Anchor
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=49208; -- Prototype Reaper
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857 WHERE `entry`=51624; -- Vanessa Anchor Bunny JMF
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.142857, `exp`=3 WHERE `entry`=49541; -- Vanessa VanCleef
UPDATE `creature_template` SET `npcflag`=16777216 WHERE `entry`=49550; -- Rope
UPDATE `gameobject_template` SET `faction`=35, `flags`=32 WHERE `entry`=208002; -- -Unknown-
UPDATE `gameobject_template` SET `flags`=34 WHERE `entry`=13965; -- Factory Door
UPDATE `gameobject_template` SET `flags`=34 WHERE `entry`=16399; -- Foundry Door
UPDATE `gameobject_template` SET `flags`=34 WHERE `entry`=16400; -- Mast Room Door
REPLACE INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(53488, 0, 0x0, 0x1, '99201'), -- Summon Enabler Stalker - Summon Enabler
(4075, 0, 0x0, 0x1, ''), -- Rat
(48229, 0, 0x0, 0x1, ''), -- Kobold Digger
(48230, 0, 0x0, 0x1, ''), -- Ogre Henchman
(48446, 0, 0x0, 0x1, '90101'), -- Scorch Mark Bunny JMF - Scorch Mark Animkit
(45979, 0, 0x0, 0x1, ''), -- General Purpose Bunny JMF
(48284, 0, 0x0, 0x1, ''), -- Mining Powder
(48266, 0, 0x0, 0x1, ''), -- Defias Cannon
(49042, 0, 0x3000000, 0x1, '46598'), -- Glubtok Firewall Platter Creature Level 2c - Ride Vehicle Hardcoded
(49040, 0, 0x3000000, 0x1, '46598'), -- Glubtok Firewall Platter Creature Level 1c - Ride Vehicle Hardcoded
(48974, 0, 0x3000000, 0x1, ''), -- Glubtok Firewall Platter
(48975, 0, 0x3000000, 0x1, '46598'), -- Glubtok Firewall Platter Creature Level 1a - Ride Vehicle Hardcoded
(48976, 0, 0x3000000, 0x1, '46598'), -- Glubtok Firewall Platter Creature Level 2a - Ride Vehicle Hardcoded
(49039, 0, 0x3000000, 0x1, '46598'), -- Glubtok Firewall Platter Creature Level 1b - Ride Vehicle Hardcoded
(49041, 0, 0x3000000, 0x1, '46598'), -- Glubtok Firewall Platter Creature Level 2b - Ride Vehicle Hardcoded
(47162, 0, 0x0, 0x1, ''), -- Glubtok
(48338, 0, 0x0, 0x1, '89842'), -- Mine Bunny - Drink Tray
(48340, 0, 0x0, 0x1, '46598'), -- Drink Tray - Ride Vehicle Hardcoded
(48341, 0, 0x0, 0x1, '46598'), -- Goblin Cocktail - Ride Vehicle Hardcoded
(48342, 0, 0x0, 0x1, '46598'), -- Goblin Cocktail - Ride Vehicle Hardcoded
(48343, 0, 0x0, 0x1, '46598'), -- Goblin Cocktail - Ride Vehicle Hardcoded
(48351, 0, 0x0, 0x1, '89842'), -- Mine Bunny - Drink Tray
(47403, 0, 0x0, 0x1, '90979'), -- Defias Reaper - Energize
(47404, 0, 0x0, 0x1, ''), -- Defias Watcher
(49208, 0, 0x0, 0x1, '87239 91731'), -- Prototype Reaper - Zero Power, Obsidian Alloy
(51624, 0, 0x0, 0x1, ''), -- Vanessa Anchor Bunny JMF
(47297, 0, 0x0, 0x1, ''), -- Lumbering Oaf
(47296, 0, 0x0, 0x1, '46598 90546'), -- Helix Gearbreaker - Ride Vehicle Hardcoded, Oafguard
(49552, 0, 0x0, 0x1, ''), -- Vanessa's Rope Anchor
(47242, 0, 0x0, 0x1, ''), -- General Purpose Bunny JMF (Look 2)
(47282, 0, 0x0, 0x1, '88164'), -- Fire Blossom Bunny - Fire Blossom Visual
(47284, 0, 0x0, 0x1, '88165'), -- Frost Blossom Bunny - Frost Blossom Visual
(48262, 0, 0x0, 0x1, ''), -- Ogre Bodyguard
(47677, 0, 0x0, 0x1, ''), -- General Purpose Bunny JMF (Look 3)
(43778, 0, 0x0, 0x1, '87239 88348'), -- Foe Reaper 5000 - Zero Power, Off-line
(48441, 0, 0x0, 0x1, ''), -- Mining Monkey
(48279, 0, 0x0, 0x1, '91035'), -- Goblin Overseer - Threatening Shout
(48278, 0, 0x0, 0x1, ''), -- Mining Monkey
(48442, 0, 0x0, 0x1, ''), -- Mining Monkey
(48440, 0, 0x0, 0x1, ''), -- Mining Monkey
(48445, 0, 0x0, 0x1, ''), -- Oaf Lackey
(48439, 0, 0x0, 0x1, '70628'), -- Goblin Engineer - Permanent Feign Death
(48280, 0, 0x0, 0x1, '70628'), -- Goblin Craftsman - Permanent Feign Death
(48502, 0, 0x0, 0x1, ''), -- Defias Enforcer
(48417, 0, 0x0, 0x1, '90389'), -- Defias Blood Wizard - Blood Channeling
(43359, 0, 0x0, 0x1, ''), -- ELM General Purpose Bunny Infinite Hide Body
(44140, 0, 0x0, 0x1, ''), -- PetWait Trigger
(37490, 0, 0x0, 0x1, ''), -- ELM General Purpose Bunny Infinite
(42851, 0, 0x0, 0x1, '29266'), -- Revenant of Neptulon - Permanent Feign Death
(42173, 0, 0x0, 0x1, ''), -- The Undershell Tentacle Flavor
(42196, 0, 0x0, 0x1, '78715'), -- ELM General Purpose Bunny Infinite (scale x2.5) - L'ghorek: Ascendant Light Beam
(40987, 0, 0x0, 0x1, ''), -- Gnash
(32520, 0, 0x0, 0x1, ''), -- Totally Generic Bunny (All Phase)
(48420, 0, 0x0, 0x1, ''), -- Defias Digger
(48419, 0, 0x0, 0x1, ''), -- Defias Miner
(48418, 0, 0x0, 0x1, '92001'), -- Defias Envoker - Envoker's Shield
(48421, 0, 0x0, 0x1, ''), -- Defias Overseer
(49139, 0, 0x0, 0x1, ''), -- Helix' Crew
(49138, 0, 0x0, 0x1, ''), -- Helix' Crew
(49136, 0, 0x0, 0x1, ''), -- Helix' Crew
(49137, 0, 0x0, 0x1, ''), -- Helix' Crew
(51462, 0, 0x0, 0x1, ''), -- Mine Rat
(48505, 0, 0x0, 0x1, '90955'), -- Defias Shadowguard - Camouflage
(48447, 0, 0x3000000, 0x1, ''), -- Monstrous Parrot
(48450, 0, 0x3000000, 0x1, ''), -- Sunwing Squawker
(47626, 0, 0x0, 0x1, '88736'), -- Admiral Ripsnarl - Thirst for Blood
(48451, 0, 0x0, 0x1, ''), -- Ol' Beaky
(48522, 0, 0x0, 0x1, ''), -- Defias Pirate
(48521, 0, 0x0, 0x1, ''), -- Defias Squallshaper
(47739, 0, 0x0, 0x1, '89339'), -- "Captain" Cookie - Who's that?
(49564, 0, 0x3000000, 0x1, '92376'), -- A Note From Vanessa - Cosmetic - Loot Sparkles
(49429, 0, 0x0, 0x1, '89279'), -- Vanessa VanCleef - Sitting
(49454, 0, 0x0, 0x1, ''), -- Vanessa's Trap Bunny
(49457, 0, 0x0, 0x1, '94557'), -- Steam Valve - CLICK ME
(51594, 0, 0x0, 0x1, '92169'), -- Glubtok Nightmare Fire Bunny - Nightmare Flames
(49671, 0, 0x0, 0x1, '48143'), -- Vanessa VanCleef - Forgotten Aura
(49670, 0, 0x0, 0x1, '48143'), -- Glubtok - Forgotten Aura
(49674, 0, 0x0, 0x1, '48143'), -- Helix Gearbreaker - Forgotten Aura
(49493, 0, 0x0, 0x1, ''), -- Nightmare Skitterling
(49495, 0, 0x0, 0x1, ''), -- Chattering Horror
(49494, 0, 0x0, 0x1, ''), -- Darkweb Devourer
(49681, 0, 0x0, 0x1, '48143'), -- Foe Reaper 5000 - Forgotten Aura
(49520, 0, 0x3000000, 0x1, '95519'), -- Vanessa Lightning Platter - Spark
(49521, 0, 0x3000000, 0x1, '92277'), -- Vanessa Lightning Stalker - Spark
(49682, 0, 0x0, 0x1, '48143'), -- Ripsnarl - Forgotten Aura
(49534, 0, 0x0, 0x1, ''), -- Emme Harrington
(49532, 0, 0x0, 0x1, ''), -- Enraged Worgen
(49535, 0, 0x0, 0x1, ''), -- Erik Harrington
(49539, 0, 0x0, 0x1, ''), -- James Harrington
(49536, 0, 0x0, 0x1, '92608'), -- Calissa Harrington - Choking
(49541, 0, 0x0, 0x1, ''), -- Vanessa VanCleef
(49550, 0, 0x0, 0x1, '95527'); -- Rope - CLICK ME
UPDATE `creature_model_info` SET `bounding_radius`=1.1385, `combat_reach`=2.15625 WHERE `modelid`=373; -- 373
UPDATE `creature_model_info` SET `bounding_radius`=0.28, `combat_reach`=0.8 WHERE `modelid`=36148; -- 36148
UPDATE `creature_model_info` SET `bounding_radius`=0.28, `combat_reach`=0.8 WHERE `modelid`=36150; -- 36150
UPDATE `creature_model_info` SET `bounding_radius`=0.28, `combat_reach`=0.8 WHERE `modelid`=36152; -- 36152
UPDATE `creature_model_info` SET `bounding_radius`=1.122, `combat_reach`=0.9 WHERE `modelid`=368; -- 368
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+791;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 53488, 36, 1, 1, -53.29514, -377.9635, 54.40679, 2.827433, 7200, 0, 0), -- Summon Enabler Stalker (Area: 0)
(@CGUID+1, 53488, 36, 1, 1, -56.35764, -395.1754, 54.72453, 2.827433, 7200, 0, 0), -- Summon Enabler Stalker (Area: 0)
(@CGUID+2, 53488, 36, 1, 1, -34.30382, -374.941, 58.93652, 2.827433, 7200, 0, 0), -- Summon Enabler Stalker (Area: 0)
(@CGUID+3, 53488, 36, 1, 1, -17.83333, -380.2656, 61.01982, 2.827433, 7200, 0, 0), -- Summon Enabler Stalker (Area: 0)
(@CGUID+4, 4075, 36, 1, 1, -33.10969, -372.5262, 58.97606, 3.006042, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+5, 53488, 36, 1, 1, -75.87153, -375.1736, 54.97334, 2.827433, 7200, 0, 0), -- Summon Enabler Stalker (Area: 0)
(@CGUID+6, 48229, 36, 1, 1, -97.08854, -391.0764, 59.05743, 0.8377581, 7200, 0, 0), -- Kobold Digger (Area: 0)
(@CGUID+7, 48230, 36, 1, 1, -97.55382, -398.875, 58.43073, 2.565634, 7200, 0, 0), -- Ogre Henchman (Area: 0) (possible waypoints or random movement)
(@CGUID+8, 48446, 36, 1, 1, -90.3924, -375.684, 58.02913, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+9, 45979, 36, 1, 1, -90.4306, -375.743, 58.01613, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+10, 48229, 36, 1, 1, -105.9931, -403.4167, 59.98793, 4.712389, 7200, 0, 0), -- Kobold Digger (Area: 0)
(@CGUID+11, 48284, 36, 1, 1, -98.1962, -388.095, 58.92353, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+12, 4075, 36, 1, 1, -101.1755, -389.3205, 57.94141, 1.963003, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+13, 48230, 36, 1, 1, -115.431, -431.451, 55.07733, 0, 7200, 0, 0), -- Ogre Henchman (Area: 0) (possible waypoints or random movement)
(@CGUID+17, 48230, 36, 1, 1, -157.3924, -396.8229, 56.56949, 5.026548, 7200, 0, 0), -- Ogre Henchman (Area: 0) (possible waypoints or random movement)
(@CGUID+18, 47162, 36, 1, 1, -192.3281, -450.2448, 54.52153, 1.605703, 7200, 0, 0), -- Glubtok (Area: 0) (possible waypoints or random movement)
(@CGUID+19, 48338, 36, 1, 1, -187.2888, -494.8318, 53.54471, 4.419672, 7200, 0, 0), -- Mine Bunny (Area: 0) (possible waypoints or random movement)
(@CGUID+20, 48351, 36, 1, 1, -213.8468, -500.7658, 50.83506, 2.51883, 7200, 0, 0), -- Mine Bunny (Area: 0) (possible waypoints or random movement)
(@CGUID+21, 47403, 36, 1, 1, -182.7431, -565.9688, 19.3898, 3.351032, 7200, 0, 0), -- Defias Reaper (Area: 0) (possible waypoints or random movement)
(@CGUID+22, 47404, 36, 1, 1, -205.5347, -552.7465, 19.3898, 4.537856, 7200, 0, 0), -- Defias Watcher (Area: 0) (possible waypoints or random movement)
(@CGUID+23, 49208, 36, 1, 1, -205.8229, -553.7934, 51.31293, 4.712389, 7200, 0, 0), -- Prototype Reaper (Area: 0)
(@CGUID+24, 51624, 36, 1, 1, -205.7691, -579.092, 51.10293, 5.986479, 7200, 0, 0), -- Vanessa Anchor Bunny JMF (Area: 0)
(@CGUID+25, 47403, 36, 1, 1, -228.6754, -565.7535, 19.38983, 5.986479, 7200, 0, 0), -- Defias Reaper (Area: 0) (possible waypoints or random movement)
(@CGUID+26, 47297, 36, 1, 1, -302.3611, -516.3455, 52.03153, 0.1745329, 7200, 0, 0), -- Lumbering Oaf (Area: 0) (possible waypoints or random movement)
(@CGUID+27, 49552, 36, 1, 1, -63.6059, -862.7864, 202.7301, 4.607669, 7200, 0, 0), -- Vanessa's Rope Anchor (Area: 0)
(@CGUID+28, 49552, 36, 1, 1, -64.21702, -866.1823, 195.3946, 4.607669, 7200, 0, 0), -- Vanessa's Rope Anchor (Area: 0)
(@CGUID+29, 49552, 36, 1, 1, -69.15452, -868.9636, 195.2482, 4.607669, 7200, 0, 0), -- Vanessa's Rope Anchor (Area: 0)
(@CGUID+30, 49552, 36, 1, 1, -71.11459, -868.4636, 200.7708, 4.607669, 7200, 0, 0), -- Vanessa's Rope Anchor (Area: 0)
(@CGUID+31, 49552, 36, 1, 1, -74.29688, -877.1007, 195.0443, 4.607669, 7200, 0, 0), -- Vanessa's Rope Anchor (Area: 0)
(@CGUID+32, 48266, 36, 1, 1, -82.3142, -775.5, 26.89333, 1.727876, 7200, 0, 0), -- Defias Cannon (Area: 0) (possible waypoints or random movement)
(@CGUID+33, 47404, 36, 1, 1, -229.724, -590.3715, 19.3898, 0.715585, 7200, 0, 0), -- Defias Watcher (Area: 0) (possible waypoints or random movement)
(@CGUID+34, 48229, 36, 1, 1, -116.497, -420.271, 56.89433, 0.9075712, 7200, 0, 0), -- Kobold Digger (Area: 0)
(@CGUID+35, 48284, 36, 1, 1, -117.422, -412.74, 58.52193, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+36, 48229, 36, 1, 1, -108.866, -426.997, 55.55853, 1.343904, 7200, 0, 0), -- Kobold Digger (Area: 0)
(@CGUID+37, 48284, 36, 1, 1, -123.663, -395.759, 58.44543, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+38, 48229, 36, 1, 1, -149.2691, -405.8733, 57.492, 3.281219, 7200, 0, 0), -- Kobold Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+39, 48284, 36, 1, 1, -137.8663, -413.4028, 58.77196, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+40, 48229, 36, 1, 1, -156.2813, -402.2587, 56.83122, 4.712389, 7200, 0, 0), -- Kobold Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+41, 48229, 36, 1, 1, -112.92, -445.181, 55.62133, 5.393067, 7200, 0, 0), -- Kobold Digger (Area: 0)
(@CGUID+42, 48229, 36, 1, 1, -126.455, -441.102, 55.52733, 4.433136, 7200, 0, 0), -- Kobold Digger (Area: 0)
(@CGUID+43, 4075, 36, 1, 1, -118.4969, -415.2892, 58.11641, 2.024032, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+44, 48229, 36, 1, 1, -168.2535, -396.3125, 57.57815, 2.844887, 7200, 0, 0), -- Kobold Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+45, 48229, 36, 1, 1, -161.342, -394.6337, 57.27974, 1.692969, 7200, 0, 0), -- Kobold Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+46, 48229, 36, 1, 1, -151.4722, -396.1979, 56.97473, 1.902409, 7200, 0, 0), -- Kobold Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+47, 48284, 36, 1, 1, -142.6979, -398.7153, 57.98805, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+48, 48284, 36, 1, 1, -168.455, -396.632, 57.56803, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+49, 48229, 36, 1, 1, -144.4861, -398.7049, 57.68261, 1.64061, 7200, 0, 0), -- Kobold Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+50, 4075, 36, 1, 1, -186.0462, -426.0557, 53.99179, 3.433048, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+51, 47242, 36, 1, 1, -175.0863, -439.2159, 55.01705, 4.119221, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+52, 47242, 36, 1, 1, -178.8307, -427.3794, 63.64943, 2.351002, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+53, 47282, 36, 1, 1, -181.7656, -416.9757, 54.75943, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+54, 48284, 36, 1, 1, -179.148, -425.917, 55.03433, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+55, 47282, 36, 1, 1, -183.901, -430.757, 54.28753, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+56, 47282, 36, 1, 1, -189.0608, -422.3871, 54.19553, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+57, 47284, 36, 1, 1, -181.1267, -423.8195, 54.84613, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+58, 47282, 36, 1, 1, -180.2517, -437.9427, 54.78763, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+59, 47284, 36, 1, 1, -176.099, -431.2413, 55.20924, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+60, 45979, 36, 1, 1, -179.307, -415.161, 55.01993, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+61, 48262, 36, 1, 1, -185.094, -428.71, 54.15053, 2.548181, 7200, 0, 0), -- Ogre Bodyguard (Area: 0) (possible waypoints or random movement)
(@CGUID+62, 48262, 36, 1, 1, -190.826, -425.172, 54.10973, 5.899213, 7200, 0, 0), -- Ogre Bodyguard (Area: 0) (possible waypoints or random movement)
(@CGUID+63, 47242, 36, 1, 1, -208.9715, -433.055, 65.18623, 1.326126, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+64, 47242, 36, 1, 1, -190.0774, -449.9595, 65.28764, 1.326129, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+65, 47284, 36, 1, 1, -181.0122, -456.1945, 54.77313, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+66, 47284, 36, 1, 1, -195.9236, -436.6458, 53.42483, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+67, 45979, 36, 1, 1, -194.4757, -433.9306, 53.52733, 4.852015, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+68, 47284, 36, 1, 1, -183.6076, -446.2066, 54.83573, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+69, 45979, 36, 1, 1, -193.2691, -442.0156, 53.71243, 1.692969, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+70, 47282, 36, 1, 1, -203.3906, -431.1389, 54.43893, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+71, 47284, 36, 1, 1, -196.9479, -427.533, 54.27064, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+72, 47282, 36, 1, 1, -190.3472, -431.7639, 53.76943, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+73, 47284, 36, 1, 1, -187.7188, -440.2847, 53.55913, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+74, 47677, 36, 1, 1, -193.3576, -442.0313, 53.71683, 1.692969, 7200, 0, 0), -- General Purpose Bunny JMF (Look 3) (Area: 0)
(@CGUID+75, 47284, 36, 1, 1, -200.8802, -440.7726, 53.44453, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+76, 47242, 36, 1, 1, -189.983, -439.3621, 65.26014, 1.368266, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+77, 47282, 36, 1, 1, -193.6944, -445.6736, 54.22083, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+78, 47282, 36, 1, 1, -188.7569, -452.1458, 54.57014, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+79, 47284, 36, 1, 1, -203.0434, -448.5625, 54.10133, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+80, 47284, 36, 1, 1, -201.2726, -462.5313, 54.36553, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+81, 47284, 36, 1, 1, -207.4792, -441.5156, 54.05593, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+82, 47282, 36, 1, 1, -214.5434, -441.151, 54.66173, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+83, 47284, 36, 1, 1, -197.2222, -453.6215, 54.89573, 0, 7200, 0, 0), -- Frost Blossom Bunny (Area: 0)
(@CGUID+84, 47242, 36, 1, 1, -209.6404, -447.6285, 65.39354, 6.27958, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+85, 47282, 36, 1, 1, -204.9931, -456.0903, 54.28944, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+86, 47242, 36, 1, 1, -198.4934, -458.0069, 65.20963, 0.9894093, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+87, 47242, 36, 1, 1, -198.3551, -448.2857, 59.50373, 1.163944, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0) (possible waypoints or random movement)
(@CGUID+88, 43778, 36, 1, 1, -209.8368, -568.6215, 21.06013, 1.972222, 7200, 0, 0), -- Foe Reaper 5000 (Area: 0) (possible waypoints or random movement)
(@CGUID+89, 48266, 36, 1, 1, -89.25694, -782.5278, 17.25636, 1.553343, 7200, 0, 0), -- Defias Cannon (Area: 0) (possible waypoints or random movement)
(@CGUID+90, 48266, 36, 1, 1, -72.1059, -786.894, 39.55383, 1.64061, 7200, 0, 0), -- Defias Cannon (Area: 0) (possible waypoints or random movement)
(@CGUID+91, 48266, 36, 1, 1, -46.81424, -783.1996, 18.49328, 1.169371, 7200, 0, 0), -- Defias Cannon (Area: 0) (possible waypoints or random movement)
(@CGUID+92, 48266, 36, 1, 1, -58.6424, -787.132, 39.35053, 1.396263, 7200, 0, 0), -- Defias Cannon (Area: 0) (possible waypoints or random movement)
(@CGUID+93, 47282, 36, 1, 1, -211.0625, -463.7135, 54.01873, 0, 7200, 0, 0), -- Fire Blossom Bunny (Area: 0)
(@CGUID+94, 48441, 36, 1, 1, -178.653, -491.51, 54.40033, 6.230825, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+95, 48284, 36, 1, 1, -182.821, -485.785, 54.13213, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+96, 48279, 36, 1, 1, -180.7778, -491.4045, 54.2247, 6.248279, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+97, 48279, 36, 1, 1, -194.712, -491.557, 53.70483, 3.036873, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+98, 48278, 36, 1, 1, -197.111, -491.161, 54.00533, 3.281219, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+99, 48441, 36, 1, 1, -204.576, -500.977, 52.41693, 1.308997, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+100, 48442, 36, 1, 1, -220.377, -485.104, 49.33203, 1.012291, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+101, 48284, 36, 1, 1, -228.181, -491.986, 48.78503, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+102, 48284, 36, 1, 1, -213.526, -496.0174, 49.79369, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+103, 48284, 36, 1, 1, -192.785, -495.118, 53.56623, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+104, 48442, 36, 1, 1, -182.979, -503.938, 53.55923, 4.834562, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+105, 48279, 36, 1, 1, -222.8681, -484.7049, 48.86404, 0.2268928, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+106, 48279, 36, 1, 1, -234.918, -487.356, 48.57053, 3.804818, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+107, 48440, 36, 1, 1, -193.194, -507.111, 53.27973, 5.340707, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+108, 48442, 36, 1, 1, -157.344, -507.266, 53.52063, 0.6457718, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+109, 48279, 36, 1, 1, -159.293, -507.467, 53.40303, 0.2268928, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+110, 48442, 36, 1, 1, -220.229, -503.561, 50.35073, 3.298672, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+111, 48440, 36, 1, 1, -168.326, -510.337, 53.55633, 4.712389, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+112, 48440, 36, 1, 1, -236.847, -489.092, 49.94863, 4.39823, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+113, 48284, 36, 1, 1, -249.444, -492.528, 49.22083, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+114, 48284, 36, 1, 1, -206.377, -511.821, 51.61583, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+115, 48445, 36, 1, 1, -258.4514, -482.1701, 49.53112, 6.195919, 7200, 0, 0), -- Oaf Lackey (Area: 0) (possible waypoints or random movement)
(@CGUID+116, 48440, 36, 1, 1, -211.255, -512.712, 50.90503, 5.235988, 7200, 0, 0), -- Mining Monkey (Area: 0) (possible waypoints or random movement)
(@CGUID+117, 48279, 36, 1, 1, -151.997, -518.648, 52.77413, 0.5934119, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+118, 48279, 36, 1, 1, -156.708, -519.698, 52.53343, 3.996804, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+119, 48278, 36, 1, 1, -150.635, -518.189, 52.99363, 0.7679449, 7200, 0, 0), -- Mining Monkey (Area: 0)
(@CGUID+120, 48440, 36, 1, 1, -157.717, -520.205, 52.49503, 2.303835, 7200, 0, 0), -- Mining Monkey (Area: 0)
(@CGUID+121, 48266, 36, 1, 1, -30.2622, -793.069, 19.23703, 0.8028514, 7200, 0, 0), -- Defias Cannon (Area: 0) (possible waypoints or random movement)
(@CGUID+122, 48266, 36, 1, 1, -40.0035, -793.302, 39.47543, 1.047198, 7200, 0, 0), -- Defias Cannon (Area: 0) (possible waypoints or random movement)
(@CGUID+123, 48284, 36, 1, 1, -149.915, -524.575, 52.22053, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+124, 48284, 36, 1, 1, -149.052, -523.596, 52.48153, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+125, 48284, 36, 1, 1, -154.483, -532.689, 49.80823, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+126, 48442, 36, 1, 1, -154.549, -530.686, 49.84943, 3.717551, 7200, 0, 0), -- Mining Monkey (Area: 0)
(@CGUID+127, 48284, 36, 1, 1, -158.8, -531.5, 52.45723, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+128, 48284, 36, 1, 1, -146.592, -528.896, 52.02183, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+129, 48284, 36, 1, 1, -158.859, -533.128, 52.41903, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+130, 48284, 36, 1, 1, -153.231, -532.743, 49.64743, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+131, 48279, 36, 1, 1, -153.231, -531.007, 49.74493, 3.176499, 7200, 0, 0), -- Goblin Overseer (Area: 0) (possible waypoints or random movement)
(@CGUID+132, 48441, 36, 1, 1, -159.908, -529.783, 52.32883, 3.01942, 7200, 0, 0), -- Mining Monkey (Area: 0)
(@CGUID+133, 48284, 36, 1, 1, -153.854, -533.601, 49.66083, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+134, 48284, 36, 1, 1, -149.479, -533.724, 49.70473, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+135, 48284, 36, 1, 1, -150.373, -533.181, 49.61183, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+136, 48442, 36, 1, 1, -147.781, -532.668, 50.38663, 5.8294, 7200, 0, 0), -- Mining Monkey (Area: 0)
(@CGUID+137, 48284, 36, 1, 1, -275.771, -502.406, 50.08163, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+138, 48439, 36, 1, 1, -180.8073, -561.8715, 51.31293, 0.5061455, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+139, 48280, 36, 1, 1, -206.7535, -554.3004, 51.31293, 5.131268, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+140, 48280, 36, 1, 1, -185.151, -559.092, 19.38983, 3.071779, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+141, 47242, 36, 1, 1, -205.1997, -561.3542, 21.06013, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+142, 48439, 36, 1, 1, -205.5781, -561.9462, 21.06013, 1.37881, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+143, 48439, 36, 1, 1, -228.8385, -561.6007, 51.31293, 3.455752, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+144, 48439, 36, 1, 1, -211.7066, -561.7882, 21.06013, 6.143559, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+145, 47242, 36, 1, 1, -200.0295, -565.434, 21.06013, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+146, 45979, 36, 1, 1, -211.7708, -564.9583, 21.06013, 1.867502, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+147, 48280, 36, 1, 1, -182.8715, -574.3906, 48.22303, 3.647738, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+148, 48439, 36, 1, 1, -222.3194, -561.1059, 19.38983, 2.356194, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+149, 47242, 36, 1, 1, -208.5521, -568.1215, 25.20743, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+150, 47242, 36, 1, 1, -206.1632, -568.8489, 24.63523, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+151, 47242, 36, 1, 1, -208.2587, -567.2917, 21.06013, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+152, 47242, 36, 1, 1, -209.2656, -569.7153, 27.31943, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+153, 47242, 36, 1, 1, -218.9653, -565.441, 21.06013, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+154, 47242, 36, 1, 1, -211.8802, -568.4844, 23.04893, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+155, 48280, 36, 1, 1, -198.2465, -571.0087, 21.06013, 3.525565, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+156, 47242, 36, 1, 1, -212.1215, -570.3924, 26.43263, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+157, 47242, 36, 1, 1, -202.276, -571.0608, 21.06013, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+158, 47242, 36, 1, 1, -216.7934, -571.9722, 21.06013, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+159, 47242, 36, 1, 1, -208.4913, -576.6979, 27.95013, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+160, 48280, 36, 1, 1, -223.0885, -575.1111, 21.06013, 3.682645, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+161, 48280, 36, 1, 1, -235.1337, -569.2188, 19.38983, 5.183628, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+162, 48280, 36, 1, 1, -216.0504, -578.4496, 21.06013, 0.5934119, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+163, 45979, 36, 1, 1, -289.5868, -489.5746, 49.91263, 4.712389, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+164, 48445, 36, 1, 1, -289.375, -501.9254, 50.2008, 4.607669, 7200, 0, 0), -- Oaf Lackey (Area: 0) (possible waypoints or random movement)
(@CGUID+165, 48439, 36, 1, 1, -183.3299, -593.0399, 40.10643, 0.3141593, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+166, 48502, 36, 1, 1, -143.554, -582.24, 18.82373, 2.9147, 7200, 0, 0), -- Defias Enforcer (Area: 0) (possible waypoints or random movement)
(@CGUID+167, 48284, 36, 1, 1, -146.743, -586.997, 18.93603, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+168, 48417, 36, 1, 1, -139.8073, -575.507, 18.88991, 3.106686, 7200, 0, 0), -- Defias Blood Wizard (Area: 0) (possible waypoints or random movement)
(@CGUID+169, 48280, 36, 1, 1, -203, -589.4427, 21.06013, 4.014257, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+170, 48502, 36, 1, 1, -144.295, -575.267, 19.13053, 3.403392, 7200, 0, 0), -- Defias Enforcer (Area: 0) (possible waypoints or random movement)
(@CGUID+171, 48417, 36, 1, 1, -139.2622, -580.5938, 18.53285, 3.106686, 7200, 0, 0), -- Defias Blood Wizard (Area: 0) (possible waypoints or random movement)
(@CGUID+172, 48284, 36, 1, 1, -127.288, -599.422, 16.89033, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+173, 48439, 36, 1, 1, -214.3663, -587.1528, 21.06013, 6.248279, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+174, 45979, 36, 1, 1, -219.9045, -585.3351, 21.06016, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+175, 48280, 36, 1, 1, -195.8906, -600.5208, 33.98453, 1.396263, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+318, 48420, 36, 1, 1, -260.2014, -571.132, 50.86203, 1.867502, 7200, 0, 0), -- Defias Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+319, 45979, 36, 1, 1, -289.809, -527.2153, 49.80213, 1.623156, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+320, 45979, 36, 1, 1, -289.1597, -505.1545, 50.09933, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+321, 48445, 36, 1, 1, -289.2934, -505.3385, 50.09231, 1.53589, 7200, 0, 0), -- Oaf Lackey (Area: 0) (possible waypoints or random movement)
(@CGUID+322, 48284, 36, 1, 1, -276.222, -579.795, 50.42633, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+323, 48419, 36, 1, 1, -282.7795, -557.5469, 49.37153, 6.230825, 7200, 0, 0), -- Defias Miner (Area: 0) (possible waypoints or random movement)
(@CGUID+324, 48284, 36, 1, 1, -296.9201, -560.7552, 49.43071, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+325, 48419, 36, 1, 1, -267.2205, -573.1736, 50.76123, 1.972222, 7200, 0, 0), -- Defias Miner (Area: 0) (possible waypoints or random movement)
(@CGUID+326, 48284, 36, 1, 1, -284.227, -550.545, 49.53033, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+327, 48418, 36, 1, 1, -289.5885, -562.243, 49.01513, 6.003932, 7200, 0, 0), -- Defias Envoker (Area: 0) (possible waypoints or random movement)
(@CGUID+328, 48419, 36, 1, 1, -285.4045, -567.7361, 49.41703, 6.003932, 7200, 0, 0), -- Defias Miner (Area: 0) (possible waypoints or random movement)
(@CGUID+329, 48284, 36, 1, 1, -250.729, -584.616, 51.22783, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+330, 48439, 36, 1, 1, -234.0885, -587.4722, 19.38983, 3.595378, 7200, 0, 0), -- Goblin Engineer (Area: 0)
(@CGUID+331, 48280, 36, 1, 1, -217.9497, -598.4254, 23.31133, 2.024582, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+332, 48284, 36, 1, 1, -302.448, -504.391, 49.54123, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+333, 4075, 36, 1, 1, -292.2289, -557.233, 48.85712, 2.140909, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+334, 4075, 36, 1, 1, -176.5866, -428.7362, 54.9092, 2.391101, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+335, 48284, 36, 1, 1, -297.9306, -587.6702, 48.31031, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+336, 48420, 36, 1, 1, -295.6389, -592.243, 49.30576, 1.239184, 7200, 0, 0), -- Defias Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+337, 48420, 36, 1, 1, -310.8767, -588.3924, 48.42021, 1.675516, 7200, 0, 0), -- Defias Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+338, 48421, 36, 1, 1, -307.7448, -606.8386, 48.02074, 4.206244, 7200, 0, 0), -- Defias Overseer (Area: 0)
(@CGUID+339, 48284, 36, 1, 1, -309.0469, -599.3316, 48.31916, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+340, 48420, 36, 1, 1, -312.842, -595.4167, 48.6128, 3.717551, 7200, 0, 0), -- Defias Digger (Area: 0) (possible waypoints or random movement)
(@CGUID+341, 48419, 36, 1, 1, -293.1337, -607.7639, 47.71781, 3.909538, 7200, 0, 0), -- Defias Miner (Area: 0) (possible waypoints or random movement)
(@CGUID+342, 48418, 36, 1, 1, -312.0383, -593.0836, 48.29668, 2.881687, 7200, 0, 0), -- Defias Envoker (Area: 0) (possible waypoints or random movement)
(@CGUID+343, 48418, 36, 1, 1, -297.1141, -594.7499, 48.30822, 0.3241625, 7200, 0, 0), -- Defias Envoker (Area: 0) (possible waypoints or random movement)
(@CGUID+344, 48419, 36, 1, 1, -276.4913, -594.5555, 51.67675, 5.427974, 7200, 0, 0), -- Defias Miner (Area: 0) (possible waypoints or random movement)
(@CGUID+345, 48421, 36, 1, 1, -306.5399, -607.9757, 47.79, 3.560472, 7200, 0, 0), -- Defias Overseer (Area: 0)
(@CGUID+346, 49139, 36, 1, 1, -283.8438, -503.3698, 60.512, 1.902409, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+347, 49138, 36, 1, 1, -285.8681, -503.8264, 60.55348, 5.009095, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+348, 49136, 36, 1, 1, -292.6788, -503.7274, 60.27357, 4.468043, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+349, 49137, 36, 1, 1, -289.8316, -503.4063, 60.36356, 1.815142, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+350, 51462, 36, 1, 1, -291.0121, -482.4896, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+351, 51462, 36, 1, 1, -290.4479, -484.3281, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+352, 51462, 36, 1, 1, -288.9879, -483.2014, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+353, 51462, 36, 1, 1, -293.7865, -483.8195, 49.15963, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+354, 51462, 36, 1, 1, -286.9445, -482.9653, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+355, 51462, 36, 1, 1, -288.1649, -484.8108, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+356, 51462, 36, 1, 1, -289.6719, -487.2222, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+357, 51462, 36, 1, 1, -291.9896, -486.2604, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+358, 51462, 36, 1, 1, -290.9045, -486.4931, 49.88789, 3.525565, 7200, 0, 0), -- Mine Rat (Area: 0)
(@CGUID+359, 49137, 36, 1, 1, -282.2639, -503.8333, 60.60244, 5.201081, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+360, 49136, 36, 1, 1, -287.474, -503.2708, 60.44886, 1.675516, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+361, 49139, 36, 1, 1, -291.0781, -504.0938, 60.25187, 4.607669, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+362, 49138, 36, 1, 1, -294.1632, -503.2326, 60.1258, 1.867502, 7200, 0, 0), -- Helix' Crew (Area: 0)
(@CGUID+363, 48280, 36, 1, 1, -206.1771, -608.375, 29.09384, 3.490659, 7200, 0, 0), -- Goblin Craftsman (Area: 0)
(@CGUID+364, 48439, 36, 1, 1, -207.7934, -550.9514, 51.31293, 3.525565, 7200, 0, 0), -- Goblin Engineer (Area: 0) (possible waypoints or random movement)
(@CGUID+365, 48280, 36, 1, 1, -212.6719, -550.0243, 51.31293, 3.787364, 7200, 0, 0), -- Goblin Craftsman (Area: 0) (possible waypoints or random movement)
(@CGUID+366, 48439, 36, 1, 1, -225.4444, -566.316, 51.31293, 3.961897, 7200, 0, 0), -- Goblin Engineer (Area: 0) (possible waypoints or random movement)
(@CGUID+367, 48280, 36, 1, 1, -234.0347, -587.6945, 51.32703, 1.64061, 7200, 0, 0), -- Goblin Craftsman (Area: 0) (possible waypoints or random movement)
(@CGUID+368, 48505, 36, 1, 1, -135.9931, -620.5208, 14.49433, 1.361357, 7200, 0, 0), -- Defias Shadowguard (Area: 0) (possible waypoints or random movement)
(@CGUID+369, 48284, 36, 1, 1, -136.859, -630.3, 14.86513, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+370, 48502, 36, 1, 1, -127.3073, -615.0139, 13.82065, 1.937315, 7200, 0, 0), -- Defias Enforcer (Area: 0) (possible waypoints or random movement)
(@CGUID+371, 48417, 36, 1, 1, -128.5642, -620.5313, 12.94842, 1.762783, 7200, 0, 0), -- Defias Blood Wizard (Area: 0) (possible waypoints or random movement)
(@CGUID+372, 48502, 36, 1, 1, -131.2222, -615.5469, 13.46481, 1.762783, 7200, 0, 0), -- Defias Enforcer (Area: 0) (possible waypoints or random movement)
(@CGUID+373, 48284, 36, 1, 1, -109.484, -621.764, 14.72533, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+374, 48505, 36, 1, 1, -121.0938, -617.8125, 13.93089, 2.635447, 7200, 0, 0), -- Defias Shadowguard (Area: 0) (possible waypoints or random movement)
(@CGUID+375, 4075, 36, 1, 1, -135.928, -631.5826, 14.59272, 2.029979, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+376, 4075, 36, 1, 1, -263.8906, -583.1023, 50.68234, 5.87236, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+377, 45979, 36, 1, 1, -106.967, -660.372, 7.505134, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+378, 48284, 36, 1, 1, -96.1215, -662.59, 7.496774, 0, 7200, 0, 0), -- Mining Powder (Area: 0)
(@CGUID+379, 48447, 36, 1, 1, -97.15555, -690.9899, 16.55914, 0.5472363, 7200, 0, 0), -- Monstrous Parrot (Area: 0) (possible waypoints or random movement)
(@CGUID+380, 48446, 36, 1, 1, -100.849, -703.773, 9.294073, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+381, 45979, 36, 1, 1, -100.849, -703.773, 9.294073, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+382, 48447, 36, 1, 1, -99.80385, -711.6337, 20.7427, 0.1884094, 7200, 0, 0), -- Monstrous Parrot (Area: 0) (possible waypoints or random movement)
(@CGUID+383, 48446, 36, 1, 1, -88.4253, -724.722, 8.675033, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+384, 45979, 36, 1, 1, -88.4253, -724.722, 8.675033, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+385, 48447, 36, 1, 1, -41.88425, -721.276, 20.88148, 0.479264, 7200, 0, 0), -- Monstrous Parrot (Area: 0) (possible waypoints or random movement)
(@CGUID+386, 48446, 36, 1, 1, -72.559, -731.221, 8.586903, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+387, 45979, 36, 1, 1, -49.3264, -730.056, 9.320483, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+388, 48447, 36, 1, 1, -55.64786, -731.0026, 16.87419, 4.72502, 7200, 0, 0), -- Monstrous Parrot (Area: 0) (possible waypoints or random movement)
(@CGUID+389, 45979, 36, 1, 1, -72.559, -731.221, 8.586903, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+390, 48446, 36, 1, 1, -49.3264, -730.056, 9.320483, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+391, 48450, 36, 1, 1, -79.34374, -723.9265, 19.04095, 0.02948481, 7200, 0, 0), -- Sunwing Squawker (Area: 0) (possible waypoints or random movement)
(@CGUID+392, 47626, 36, 1, 1, -66.7813, -837.863, 41.06303, 4.607669, 7200, 0, 0), -- Admiral Ripsnarl (Area: 0) (possible waypoints or random movement)
(@CGUID+393, 48505, 36, 1, 1, -98.4774, -672.389, 7.502654, 1.239184, 7200, 0, 0), -- Defias Shadowguard (Area: 0) (possible waypoints or random movement)
(@CGUID+394, 48417, 36, 1, 1, -100.878, -676.349, 7.499623, 1.780236, 7200, 0, 0), -- Defias Blood Wizard (Area: 0) (possible waypoints or random movement)
(@CGUID+395, 48502, 36, 1, 1, -101.089, -673.014, 7.501654, 1.797689, 7200, 0, 0), -- Defias Enforcer (Area: 0) (possible waypoints or random movement)
(@CGUID+396, 48417, 36, 1, 1, -97.467, -675.726, 7.502423, 1.780236, 7200, 0, 0), -- Defias Blood Wizard (Area: 0) (possible waypoints or random movement)
(@CGUID+397, 45979, 36, 1, 1, -30.6337, -727.731, 8.521023, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+398, 48446, 36, 1, 1, -30.6337, -727.731, 8.521023, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+399, 48451, 36, 1, 1, -136.896, -767.099, 4.043903, 0.9424778, 7200, 0, 0), -- Ol' Beaky (Area: 0) (possible waypoints or random movement)
(@CGUID+400, 48522, 36, 1, 1, -81.4913, -779.387, 26.79513, 1.797689, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+401, 48447, 36, 1, 1, -19.56633, -727.7628, 18.43702, 0.5960214, 7200, 0, 0), -- Monstrous Parrot (Area: 0) (possible waypoints or random movement)
(@CGUID+402, 4075, 36, 1, 1, -75.23913, -778.5317, 17.48409, 0.0352346, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+403, 45979, 36, 1, 1, -12.0556, -740.252, 9.109463, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+404, 48446, 36, 1, 1, -12.0556, -740.252, 9.109463, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+405, 48522, 36, 1, 1, -87.74132, -786.2518, 17.31775, 1.762783, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+406, 48522, 36, 1, 1, -48.22222, -786.1788, 18.42003, 1.099557, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+407, 48450, 36, 1, 1, -5.154763, -753.6686, 17.02661, 3.499498, 7200, 0, 0), -- Sunwing Squawker (Area: 0) (possible waypoints or random movement)
(@CGUID+408, 48521, 36, 1, 1, -89.67709, -786.6146, 17.27533, 1.727876, 7200, 0, 0), -- Defias Squallshaper (Area: 0) (possible waypoints or random movement)
(@CGUID+409, 48521, 36, 1, 1, -42.7743, -784.259, 18.5858, 1.051801, 7200, 0, 0), -- Defias Squallshaper (Area: 0) (possible waypoints or random movement)
(@CGUID+410, 48522, 36, 1, 1, -72.0347, -790.8, 39.33693, 1.780236, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+411, 48522, 36, 1, 1, -59.0538, -791.024, 39.18833, 1.37881, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+412, 48521, 36, 1, 1, -66.72312, -793.1108, 39.49753, 3.068086, 7200, 0, 0), -- Defias Squallshaper (Area: 0) (possible waypoints or random movement)
(@CGUID+413, 48522, 36, 1, 1, -123.4896, -786.2188, 17.56621, 1.919862, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+414, 45979, 36, 1, 1, -64.25521, -820.2448, 41.23743, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+415, 47677, 36, 1, 1, -63.7604, -820.811, 41.28753, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 3) (Area: 0)
(@CGUID+416, 45979, 36, 1, 1, -65.05729, -818.691, 41.15532, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+417, 48522, 36, 1, 1, -32.6267, -795.549, 19.08903, 0.6981317, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+418, 48522, 36, 1, 1, -42.0486, -796.323, 39.42853, 0.9948376, 7200, 0, 0), -- Defias Pirate (Area: 0) (possible waypoints or random movement)
(@CGUID+419, 45979, 36, 1, 1, 0.512153, -768.229, 9.801343, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+420, 48446, 36, 1, 1, 0.512153, -768.229, 9.801343, 0, 7200, 0, 0), -- Scorch Mark Bunny JMF (Area: 0)
(@CGUID+421, 48447, 36, 1, 1, -1.246923, -779.7975, 21.63169, 2.617049, 7200, 0, 0), -- Monstrous Parrot (Area: 0) (possible waypoints or random movement)
(@CGUID+422, 48522, 36, 1, 1, -19.5833, -832.882, 19.80213, 3.508112, 7200, 0, 0), -- Defias Pirate (Area: 0)
(@CGUID+423, 48521, 36, 1, 1, -22.316, -833.927, 19.64273, 0.1396263, 7200, 0, 0), -- Defias Squallshaper (Area: 0)
(@CGUID+424, 48522, 36, 1, 1, -31.9462, -845.813, 19.17583, 6.178465, 7200, 0, 0), -- Defias Pirate (Area: Ironclad Cove)
(@CGUID+425, 48522, 36, 1, 1, -29.5, -846.29, 19.31063, 3.560472, 7200, 0, 0), -- Defias Pirate (Area: Ironclad Cove)
(@CGUID+426, 48521, 36, 1, 1, -32.0191, -847.84, 19.18763, 0.5585054, 7200, 0, 0), -- Defias Squallshaper (Area: Ironclad Cove)
(@CGUID+427, 48521, 36, 1, 1, -91.2517, -852.661, 17.26573, 5.550147, 7200, 0, 0), -- Defias Squallshaper (Area: Ironclad Cove)
(@CGUID+428, 48521, 36, 1, 1, -89.0278, -854.734, 17.30503, 2.495821, 7200, 0, 0), -- Defias Squallshaper (Area: Ironclad Cove)
(@CGUID+429, 48522, 36, 1, 1, -45.6111, -851.63, 18.56233, 4.799655, 7200, 0, 0), -- Defias Pirate (Area: Ironclad Cove)
(@CGUID+430, 48522, 36, 1, 1, -48.3003, -852.727, 18.45573, 5.393067, 7200, 0, 0), -- Defias Pirate (Area: Ironclad Cove)
(@CGUID+431, 48522, 36, 1, 1, -108.859, -843.837, 17.05493, 5.689773, 7200, 0, 0), -- Defias Pirate (Area: 0)
(@CGUID+432, 48522, 36, 1, 1, -105.021, -843.693, 17.12623, 4.171337, 7200, 0, 0), -- Defias Pirate (Area: 0)
(@CGUID+433, 48521, 36, 1, 1, -124.783, -834.497, 16.92623, 5.986479, 7200, 0, 0), -- Defias Squallshaper (Area: 0)
(@CGUID+434, 48521, 36, 1, 1, -121.389, -832.83, 17.02713, 4.066617, 7200, 0, 0), -- Defias Squallshaper (Area: 0)
(@CGUID+435, 48522, 36, 1, 1, -121.691, -835.438, 16.96713, 2.6529, 7200, 0, 0), -- Defias Pirate (Area: 0)
(@CGUID+436, 48521, 36, 1, 1, -103.72, -846.056, 17.11343, 3.071779, 7200, 0, 0), -- Defias Squallshaper (Area: 0)
(@CGUID+437, 48522, 36, 1, 1, -107.352, -847.233, 17.03343, 1.082104, 7200, 0, 0), -- Defias Pirate (Area: 0)
(@CGUID+438, 47242, 36, 1, 1, -57.3889, -822.721, 41.91503, 3.246312, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+439, 47242, 36, 1, 1, -56.4115, -827.823, 42.01633, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+440, 47242, 36, 1, 1, -62.6597, -823.653, 41.40153, 2.059489, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+441, 47242, 36, 1, 1, -62.6597, -823.653, 41.40153, 2.059489, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+442, 47242, 36, 1, 1, -61.9878, -829.885, 41.50033, 2.443461, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+443, 47242, 36, 1, 1, -56.901, -818.264, 41.95403, 2.460914, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+444, 45979, 36, 1, 1, -64.43924, -819.9375, 41.21879, 0.05235988, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+445, 47242, 36, 1, 1, -56.9514, -832.986, 41.97313, 2.059489, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+446, 47242, 36, 1, 1, -51.8299, -829.847, 42.45503, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+447, 45979, 36, 1, 1, -66.8785, -820.351, 40.97763, 0.05235988, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+448, 45979, 36, 1, 1, -66.8785, -820.351, 40.97763, 0.05235988, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+449, 47242, 36, 1, 1, -68.1302, -822.918, 40.88803, 4.08407, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+450, 47242, 36, 1, 1, -65.401, -833.352, 41.20173, 2.146755, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+451, 47242, 36, 1, 1, -51.8837, -833.491, 42.46043, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+452, 47242, 36, 1, 1, -68.934, -829.365, 40.87723, 3.106686, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+453, 47242, 36, 1, 1, -60.9792, -835.979, 41.59823, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+454, 47242, 36, 1, 1, -62.6927, -814.031, 41.38433, 4.328416, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+455, 47242, 36, 1, 1, -58.0365, -812.931, 41.83743, 5.67232, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+456, 47242, 36, 1, 1, -47.4358, -831.122, 42.87633, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+457, 47242, 36, 1, 1, -67.70139, -814.1632, 40.93637, 3.769911, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+458, 47242, 36, 1, 1, -72.9931, -825.99, 40.48343, 0.2443461, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+459, 47242, 36, 1, 1, -53.2882, -810.453, 42.28443, 2.478368, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+460, 47242, 36, 1, 1, -73.9705, -819.941, 40.35883, 4.380776, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+461, 47242, 36, 1, 1, -70.941, -835.523, 40.68593, 4.171337, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+462, 47242, 36, 1, 1, -60, -807.571, 41.64553, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+463, 47242, 36, 1, 1, -75.5295, -831.818, 40.27493, 2.460914, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+464, 47242, 36, 1, 1, -73.6458, -814.604, 40.40203, 3.979351, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+465, 47242, 36, 1, 1, -55.0469, -805.922, 42.10873, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+466, 47242, 36, 1, 1, -47.6163, -808.856, 42.82733, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+467, 47242, 36, 1, 1, -66.6615, -805.149, 41.03343, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+468, 47242, 36, 1, 1, -72.8733, -808.346, 40.48073, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+469, 47242, 36, 1, 1, -79.2431, -834.884, 39.97583, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+470, 47242, 36, 1, 1, -82.5642, -830.498, 39.70443, 5.393067, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+471, 47242, 36, 1, 1, -79.3229, -806.665, 39.93003, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+472, 47242, 36, 1, 1, -88.1024, -831.63, 39.25593, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+473, 47242, 36, 1, 1, -85.6667, -808.549, 39.42283, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+474, 47242, 36, 1, 1, -95.3628, -828.319, 38.68673, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+475, 47242, 36, 1, 1, -94.2292, -809.929, 38.74693, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+476, 47242, 36, 1, 1, -99.684, -818.974, 38.35423, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+477, 47242, 36, 1, 1, -101.174, -824.677, 38.25353, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+478, 47242, 36, 1, 1, -101.122, -813.936, 38.24383, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+479, 47242, 36, 1, 1, -104.384, -819.276, 38.02033, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+480, 4075, 36, 1, 1, -117.246, -409.9308, 59.00196, 4.009674, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+481, 4075, 36, 1, 1, -117.7326, -618.5919, 14.12225, 5.554124, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+482, 47626, 36, 1, 1, -66.7813, -837.863, 41.06303, 4.607669, 7200, 0, 0), -- Admiral Ripsnarl (Area: 0) (possible waypoints or random movement)
(@CGUID+483, 4075, 36, 1, 1, -121.0871, -802.7612, 16.93635, 1.862152, 7200, 0, 0), -- Rat (Area: 0)
(@CGUID+484, 47242, 36, 1, 1, -65.401, -833.352, 41.20173, 2.146755, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+485, 47242, 36, 1, 1, -60.9792, -835.979, 41.59823, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+486, 47242, 36, 1, 1, -61.9878, -829.885, 41.50033, 2.443461, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+487, 47242, 36, 1, 1, -56.9514, -832.986, 41.97313, 2.059489, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+488, 47242, 36, 1, 1, -68.934, -829.365, 40.87723, 3.106686, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+489, 47242, 36, 1, 1, -70.941, -835.523, 40.68593, 4.171337, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+490, 47242, 36, 1, 1, -56.4115, -827.823, 42.01633, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+491, 47242, 36, 1, 1, -62.6597, -823.653, 41.40153, 2.059489, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+492, 47242, 36, 1, 1, -62.6597, -823.653, 41.40153, 2.059489, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+493, 47242, 36, 1, 1, -51.8837, -833.491, 42.46043, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+494, 47242, 36, 1, 1, -51.8299, -829.847, 42.45503, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+495, 47242, 36, 1, 1, -68.1302, -822.918, 40.88803, 4.08407, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+496, 47242, 36, 1, 1, -57.3889, -822.721, 41.91503, 3.246312, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+497, 47242, 36, 1, 1, -72.9931, -825.99, 40.48343, 0.2443461, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+498, 47242, 36, 1, 1, -75.5295, -831.818, 40.27493, 2.460914, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+499, 45979, 36, 1, 1, -64.43924, -819.9375, 41.21879, 0.05235988, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+500, 45979, 36, 1, 1, -66.8785, -820.351, 40.97763, 0.05235988, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+501, 45979, 36, 1, 1, -66.8785, -820.351, 40.97763, 0.05235988, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+502, 47242, 36, 1, 1, -47.4358, -831.122, 42.87633, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+503, 47242, 36, 1, 1, -79.2431, -834.884, 39.97583, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+504, 47242, 36, 1, 1, -56.901, -818.264, 41.95403, 2.460914, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+505, 47242, 36, 1, 1, -73.9705, -819.941, 40.35883, 4.380776, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+506, 47242, 36, 1, 1, -62.6927, -814.031, 41.38433, 4.328416, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+507, 47242, 36, 1, 1, -82.5642, -830.498, 39.70443, 5.393067, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+508, 47242, 36, 1, 1, -67.70139, -814.1632, 40.93637, 3.769911, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+509, 47242, 36, 1, 1, -58.0365, -812.931, 41.83743, 5.67232, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+510, 47242, 36, 1, 1, -73.6458, -814.604, 40.40203, 3.979351, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+511, 47242, 36, 1, 1, -53.2882, -810.453, 42.28443, 2.478368, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+512, 47242, 36, 1, 1, -88.1024, -831.63, 39.25593, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+513, 47242, 36, 1, 1, -60, -807.571, 41.64553, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+514, 47242, 36, 1, 1, -72.8733, -808.346, 40.48073, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+515, 47242, 36, 1, 1, -66.6615, -805.149, 41.03343, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+516, 47242, 36, 1, 1, -55.0469, -805.922, 42.10873, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+517, 47242, 36, 1, 1, -47.6163, -808.856, 42.82733, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+518, 47242, 36, 1, 1, -79.3229, -806.665, 39.93003, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+519, 47242, 36, 1, 1, -95.3628, -828.319, 38.68673, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+520, 47242, 36, 1, 1, -85.6667, -808.549, 39.42283, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+521, 47242, 36, 1, 1, -94.2292, -809.929, 38.74693, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+522, 47242, 36, 1, 1, -101.174, -824.677, 38.25353, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+523, 47242, 36, 1, 1, -99.684, -818.974, 38.35423, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+524, 47242, 36, 1, 1, -101.122, -813.936, 38.24383, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+525, 47242, 36, 1, 1, -104.384, -819.276, 38.02033, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Look 2) (Area: 0)
(@CGUID+526, 47739, 36, 1, 1, -88.13194, -819.3299, 39.23453, 0, 7200, 0, 0), -- "Captain" Cookie (Area: 0) (possible waypoints or random movement)
(@CGUID+527, 49564, 36, 1, 1, -74.36111, -820.0139, 40.37145, 4.014257, 7200, 0, 0), -- A Note From Vanessa (Area: 0)
(@CGUID+528, 49429, 36, 1, 1, -75.58507, -819.9636, 47.06727, 6.178465, 7200, 0, 0), -- Vanessa VanCleef (Area: 0) (possible waypoints or random movement)
(@CGUID+529, 49454, 36, 1, 1, -205.7569, -579.0972, 42.98623, 0, 7200, 0, 0), -- Vanessa's Trap Bunny (Area: 0) (possible waypoints or random movement)
(@CGUID+530, 45979, 36, 1, 1, -52.13195, -816.1077, 51.65916, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+531, 49457, 36, 1, 1, -199.1944, -583.1545, 37.33158, 2.600541, 7200, 0, 0), -- Steam Valve (Area: 0)
(@CGUID+532, 49457, 36, 1, 1, -201.809, -572.6215, 37.33158, 4.171337, 7200, 0, 0), -- Steam Valve (Area: 0)
(@CGUID+533, 49457, 36, 1, 1, -209.6823, -585.8924, 37.33158, 0.9599311, 7200, 0, 0), -- Steam Valve (Area: 0)
(@CGUID+534, 49457, 36, 1, 1, -212.3524, -575.3976, 37.33158, 5.707227, 7200, 0, 0), -- Steam Valve (Area: 0)
(@CGUID+535, 45979, 36, 1, 1, -230.2951, -574.7708, 51.30646, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+536, 51594, 36, 1, 1, -192.2031, -595.9636, 36.37407, 2.80998, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+537, 49671, 36, 1, 1, -230.717, -563.0139, 51.31293, 1.047198, 7200, 0, 0), -- Vanessa VanCleef (Area: 0) (possible waypoints or random movement)
(@CGUID+538, 51594, 36, 1, 1, -220.625, -577.9618, 21.06016, 2.513274, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+539, 51594, 36, 1, 1, -205.3056, -563.6285, 21.06016, 5.253441, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+540, 51594, 36, 1, 1, -214.8958, -546.7136, 19.3898, 4.712389, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+541, 51594, 36, 1, 1, -207.8004, -570.6441, 21.06016, 1.762783, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+542, 51594, 36, 1, 1, -221.4653, -549.9358, 19.3898, 3.211406, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+543, 51594, 36, 1, 1, -229.9635, -559.2552, 19.3898, 0, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+544, 51594, 36, 1, 1, -216.8438, -568.9011, 21.06016, 3.909538, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+545, 51594, 36, 1, 1, -235.9045, -563.3906, 19.3898, 0, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+546, 51594, 36, 1, 1, -226.6736, -580.8316, 20.43056, 2.775074, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+547, 51594, 36, 1, 1, -227.5226, -595.1979, 20.42358, 4.206244, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+548, 51594, 36, 1, 1, -215.0399, -576.3941, 21.06016, 3.735005, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+549, 51594, 36, 1, 1, -210.592, -583.4739, 21.06016, 0, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+550, 51594, 36, 1, 1, -228.592, -553.1684, 19.3898, 5.550147, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+551, 51594, 36, 1, 1, -220.4879, -596.382, 21.95116, 0, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+552, 51594, 36, 1, 1, -190.4774, -552.2778, 51.31293, 5.305801, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+553, 51594, 36, 1, 1, -195.6267, -550.4393, 51.31293, 3.752458, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+554, 51594, 36, 1, 1, -209.7257, -557.1042, 51.31293, 3.525565, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+555, 51594, 36, 1, 1, -187.9531, -567.0469, 51.31293, 5.305801, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+556, 51594, 36, 1, 1, -185.2083, -562.4844, 19.3898, 0.9599311, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+557, 49670, 36, 1, 1, -229.3403, -560.3629, 51.31293, 5.742133, 7200, 0, 0), -- Glubtok (Area: 0)
(@CGUID+558, 51594, 36, 1, 1, -183.4236, -577.2674, 46.87183, 3.944444, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+559, 51594, 36, 1, 1, -184.6528, -572.3663, 49.27317, 3.159046, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+560, 51594, 36, 1, 1, -191.2205, -581.4965, 21.06015, 2.007129, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+561, 51594, 36, 1, 1, -201.224, -570.6788, 21.06016, 3.577925, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+562, 51594, 36, 1, 1, -198.4653, -580.757, 21.06015, 0.8901179, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+563, 51594, 36, 1, 1, -196.8767, -574.9688, 21.06016, 4.29351, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+564, 51594, 36, 1, 1, -194.1302, -548.3055, 19.3898, 4.153883, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+565, 51594, 36, 1, 1, -187.3333, -550.8143, 19.3898, 3.385939, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+566, 51594, 36, 1, 1, -186.9792, -556.8472, 19.3898, 4.153883, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+567, 51594, 36, 1, 1, -196.5504, -587.7031, 21.06015, 1.27409, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+568, 51594, 36, 1, 1, -241.5938, -578.6858, 19.3898, 2.775074, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+569, 51594, 36, 1, 1, -226.1615, -573.8021, 20.40991, 5.218534, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+570, 51594, 36, 1, 1, -181.2379, -555.3177, 19.3898, 0.3141593, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+571, 51594, 36, 1, 1, -216.5399, -602.6528, 24.88029, 2.687807, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+572, 51594, 36, 1, 1, -210.7431, -603.2813, 27.17259, 4.904375, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+573, 51594, 36, 1, 1, -225.6962, -601.3871, 21.82762, 4.555309, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+574, 51594, 36, 1, 1, -221.8629, -607.2205, 23.7542, 4.939282, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+575, 51594, 36, 1, 1, -215.7205, -608.4722, 25.87703, 2.530727, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+576, 51594, 36, 1, 1, -178.2031, -594.9965, 40.6501, 4.415683, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+577, 51594, 36, 1, 1, -197.1007, -609.7257, 32.38494, 0, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+578, 51594, 36, 1, 1, -201.9757, -611.8663, 30.62297, 2.897247, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+579, 49670, 36, 1, 1, -174.8212, -579.7552, 19.39602, 3.193953, 7200, 0, 0), -- Glubtok (Area: 0) (possible waypoints or random movement)
(@CGUID+580, 45979, 36, 1, 1, -211.9184, -581.8212, 21.06016, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+581, 49674, 36, 1, 1, -172.6858, -580.0469, 19.39752, 3.176499, 7200, 0, 0), -- Helix Gearbreaker (Area: 0) (possible waypoints or random movement)
(@CGUID+582, 49671, 36, 1, 1, -172.809, -576.9114, 19.39756, 4.817109, 7200, 0, 0), -- Vanessa VanCleef (Area: 0) (possible waypoints or random movement)
(@CGUID+583, 49493, 36, 1, 1, -184.9618, -552.9132, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+584, 49493, 36, 1, 1, -199.1406, -573.6893, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+585, 49493, 36, 1, 1, -194.5851, -578.3386, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+586, 49493, 36, 1, 1, -193.3264, -569.809, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+587, 49493, 36, 1, 1, -185.7622, -566.6059, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+588, 49493, 36, 1, 1, -181.401, -561.684, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+589, 49493, 36, 1, 1, -221.2569, -549.3316, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+590, 49493, 36, 1, 1, -215.125, -546.0486, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+591, 49493, 36, 1, 1, -210.3854, -550.6736, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+592, 49493, 36, 1, 1, -206.8715, -545.3837, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+593, 49493, 36, 1, 1, -208.3247, -556.5833, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+594, 49493, 36, 1, 1, -203.1233, -550.8281, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+595, 49493, 36, 1, 1, -198.2465, -546.9288, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+596, 49493, 36, 1, 1, -178.6389, -564.4479, 19.39, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+597, 49493, 36, 1, 1, -193.3698, -581.8663, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+598, 49493, 36, 1, 1, -188.1788, -578.3715, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+599, 49493, 36, 1, 1, -185.3385, -562.592, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+600, 49493, 36, 1, 1, -179.6458, -557.9063, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+601, 49493, 36, 1, 1, -226.5208, -587.257, 19.53274, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+602, 49493, 36, 1, 1, -199.3351, -586.7952, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+603, 49493, 36, 1, 1, -207.6545, -594.809, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+604, 49493, 36, 1, 1, -201.2587, -593.309, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+605, 49493, 36, 1, 1, -224.2743, -592.7917, 20.29579, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+606, 49493, 36, 1, 1, -211.9844, -569.5417, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+607, 49493, 36, 1, 1, -208.9288, -563.6094, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+608, 49493, 36, 1, 1, -200.8715, -557.2518, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+609, 49493, 36, 1, 1, -196.2396, -553.6927, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+610, 49493, 36, 1, 1, -192.1163, -550.1024, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+611, 49493, 36, 1, 1, -202.4063, -563.1337, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+612, 49493, 36, 1, 1, -195.9635, -560.8889, 20.58139, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+613, 49493, 36, 1, 1, -190.1094, -557.4722, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+614, 49493, 36, 1, 1, -199.3229, -550.3785, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+615, 49493, 36, 1, 1, -195.2552, -557.0087, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+616, 49493, 36, 1, 1, -190.1372, -553.0625, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+617, 49493, 36, 1, 1, -185.2118, -557.6406, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+618, 49493, 36, 1, 1, -190.6406, -561.441, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+619, 49493, 36, 1, 1, -197.7413, -564.3021, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+620, 49493, 36, 1, 1, -215.5365, -549.8021, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+621, 49493, 36, 1, 1, -212.1719, -555.0226, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+622, 49493, 36, 1, 1, -213.2344, -561.8577, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+623, 49493, 36, 1, 1, -208.5451, -568.1146, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+624, 49493, 36, 1, 1, -202.7257, -572.5174, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+625, 49493, 36, 1, 1, -205.6354, -559.1563, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+626, 49493, 36, 1, 1, -206.1615, -553.3507, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+627, 49493, 36, 1, 1, -202.5451, -546.118, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+628, 49493, 36, 1, 1, -204.1024, -596.7518, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+629, 49493, 36, 1, 1, -204.0087, -590.8386, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+630, 49493, 36, 1, 1, -198.8316, -591.7239, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+631, 49493, 36, 1, 1, -195.4375, -586.2934, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+632, 49493, 36, 1, 1, -197.6493, -582.4653, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+633, 49493, 36, 1, 1, -219.1337, -559.7899, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+634, 49493, 36, 1, 1, -221.4063, -553.1406, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+635, 49493, 36, 1, 1, -216.1215, -564.882, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+636, 49493, 36, 1, 1, -199.3125, -578.1996, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+637, 49493, 36, 1, 1, -204.684, -569.3542, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+638, 49493, 36, 1, 1, -197.8576, -569.3489, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+639, 49493, 36, 1, 1, -191.7656, -565.8559, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+640, 49493, 36, 1, 1, -213.4635, -591.625, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+641, 49493, 36, 1, 1, -206.0781, -588.0712, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+642, 49493, 36, 1, 1, -213.1997, -585.125, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+643, 49493, 36, 1, 1, -220.5174, -581.8143, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+644, 49493, 36, 1, 1, -182.8004, -569.368, 19.39167, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+645, 49493, 36, 1, 1, -189.0191, -571.2674, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+646, 49493, 36, 1, 1, -193.7674, -574.7014, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+647, 49493, 36, 1, 1, -226.1285, -581.059, 20.79114, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+648, 49495, 36, 1, 1, -218.6076, -581.0746, 21.06016, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+649, 49493, 36, 1, 1, -216.1094, -576.8264, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+650, 49495, 36, 1, 1, -222.1545, -555.1077, 19.3898, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+651, 49495, 36, 1, 1, -212.6059, -567.2239, 21.06016, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+652, 49495, 36, 1, 1, -203.9184, -551.0608, 19.3898, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+653, 49495, 36, 1, 1, -202.8663, -590.1371, 21.06016, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+654, 49495, 36, 1, 1, -196.4757, -573.0833, 21.06016, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+655, 49495, 36, 1, 1, -185.9288, -558.125, 19.3898, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+656, 49493, 36, 1, 1, -213.8767, -559.3125, 20.02806, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+657, 49493, 36, 1, 1, -221.8142, -556.3976, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+658, 49493, 36, 1, 1, -216.5017, -553.9722, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+659, 49493, 36, 1, 1, -223.7483, -574.9896, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+660, 49493, 36, 1, 1, -226.1215, -563.0382, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+661, 49493, 36, 1, 1, -213.8559, -574.6094, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+662, 49493, 36, 1, 1, -208.3854, -571.8004, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+663, 49493, 36, 1, 1, -224.5625, -568.1476, 19.92673, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+664, 49493, 36, 1, 1, -219.7083, -588.6094, 21.06015, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+665, 49493, 36, 1, 1, -218.8872, -570.5643, 21.06016, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+666, 49493, 36, 1, 1, -221.8264, -562.2795, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+667, 49493, 36, 1, 1, -227.9063, -559.566, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+668, 49493, 36, 1, 1, -230.4948, -566.0191, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+669, 49493, 36, 1, 1, -227.0243, -552.6736, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+670, 49493, 36, 1, 1, -231.566, -572.1979, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+671, 49494, 36, 1, 1, -215.7064, -553.3212, 51.29544, 0.7243207, 7200, 0, 0), -- Darkweb Devourer (Area: 0)
(@CGUID+672, 49493, 36, 1, 1, -231.8802, -578.5677, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+673, 49493, 36, 1, 1, -232.4462, -562.8837, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+674, 49495, 36, 1, 1, -233.625, -570.5868, 19.3898, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+675, 49493, 36, 1, 1, -232.4514, -586.2518, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+676, 49493, 36, 1, 1, -230.3767, -592.8577, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+677, 49495, 36, 1, 1, -232.8004, -591.1805, 19.3898, 0, 7200, 0, 0), -- Chattering Horror (Area: 0)
(@CGUID+678, 45979, 36, 1, 1, -205.4688, -567.2049, 21.06016, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+679, 49493, 36, 1, 1, -234.5208, -559.4809, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+680, 49493, 36, 1, 1, -236.5712, -565.5573, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+681, 49493, 36, 1, 1, -237.5799, -571.5903, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+682, 49493, 36, 1, 1, -238.9063, -578.1528, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+683, 49494, 36, 1, 1, -229.285, -568.6863, 51.31313, 0.8218399, 7200, 0, 0), -- Darkweb Devourer (Area: 0)
(@CGUID+684, 49493, 36, 1, 1, -234.0608, -598, 19.95063, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+685, 49493, 36, 1, 1, -236.5122, -591.9913, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+686, 49493, 36, 1, 1, -238.8021, -584.8594, 19.3898, 0, 7200, 0, 0), -- Nightmare Skitterling (Area: 0)
(@CGUID+687, 49494, 36, 1, 1, -231.3453, -584.1043, 51.31514, 1.05134, 7200, 0, 0), -- Darkweb Devourer (Area: 0)
(@CGUID+688, 49671, 36, 1, 1, -159.3924, -580.5174, 19.39817, 6.195919, 7200, 0, 0), -- Vanessa VanCleef (Area: 0)
(@CGUID+689, 49681, 36, 1, 1, -155.4705, -580.6945, 19.39779, 0, 7200, 0, 0), -- Foe Reaper 5000 (Area: 0)
(@CGUID+690, 49520, 36, 1, 1, -120.9898, -638.3776, 12.34728, 0.03183358, 7200, 0, 0), -- Vanessa Lightning Platter (Area: 0)
(@CGUID+691, 49520, 36, 1, 1, -135.3954, -623.0512, 14.44327, 0.03133297, 7200, 0, 0), -- Vanessa Lightning Platter (Area: 0)
(@CGUID+692, 49520, 36, 1, 1, -120.1581, -617.6207, 14.24549, 6.252115, 7200, 0, 0), -- Vanessa Lightning Platter (Area: 0)
(@CGUID+693, 49520, 36, 1, 1, -136.7385, -604.6659, 15.53128, 0.03079747, 7200, 0, 0), -- Vanessa Lightning Platter (Area: 0)
(@CGUID+694, 49520, 36, 1, 1, -130.4809, -586.5009, 18.57832, 0.03022512, 7200, 0, 0), -- Vanessa Lightning Platter (Area: 0)
(@CGUID+695, 49520, 36, 1, 1, -143.004, -574.9209, 19.1443, 6.253215, 7200, 0, 0), -- Vanessa Lightning Platter (Area: 0)
(@CGUID+696, 49520, 36, 1, 1, -100.6998, -648.0762, 9.095217, 2.126812, 7200, 0, 0), -- Vanessa Lightning Platter (Area: 0)
(@CGUID+697, 49681, 36, 1, 1, -101.4549, -663.6493, 7.505813, 1.850049, 7200, 0, 0), -- Foe Reaper 5000 (Area: 0) (possible waypoints or random movement)
(@CGUID+698, 45979, 36, 1, 1, -96.04688, -694.434, 8.508634, 0, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+699, 49682, 36, 1, 1, -101.2135, -663.4531, 7.504823, 1.867502, 7200, 0, 0), -- Ripsnarl (Area: 0)
(@CGUID+700, 49671, 36, 1, 1, -98.5816, -662.6632, 7.498006, 3.490659, 7200, 0, 0), -- Vanessa VanCleef (Area: 0)
(@CGUID+701, 49534, 36, 1, 1, -98.63194, -721.6268, 8.547067, 1.53589, 7200, 0, 0), -- Emme Harrington (Area: 0)
(@CGUID+702, 49532, 36, 1, 1, -97.79166, -717.8542, 8.668088, 4.520403, 7200, 0, 0), -- Enraged Worgen (Area: 0) (possible waypoints or random movement)
(@CGUID+703, 49532, 36, 1, 1, -94.40278, -719.7274, 8.598646, 3.560472, 7200, 0, 0), -- Enraged Worgen (Area: 0) (possible waypoints or random movement)
(@CGUID+704, 49532, 36, 1, 1, -101.9167, -718.7552, 8.726379, 5.51524, 7200, 0, 0), -- Enraged Worgen (Area: 0) (possible waypoints or random movement)
(@CGUID+705, 49532, 36, 1, 1, 3.326038, -760.3063, 9.713999, 5.31516, 7200, 0, 0), -- Enraged Worgen (Area: 0)
(@CGUID+706, 49532, 36, 1, 1, 8.798013, -762.2252, 9.625132, 3.379143, 7200, 0, 0), -- Enraged Worgen (Area: 0)
(@CGUID+707, 49532, 36, 1, 1, 4.232807, -766.6125, 9.804724, 1.292649, 7200, 0, 0), -- Enraged Worgen (Area: 0)
(@CGUID+708, 49535, 36, 1, 1, 5.239583, -763.0868, 9.800426, 2.007129, 7200, 0, 0), -- Erik Harrington (Area: 0)
(@CGUID+709, 49539, 36, 1, 1, -83.16319, -774.9636, 26.90351, 1.710423, 7200, 0, 0), -- James Harrington (Area: Ironclad Cove) (possible waypoints or random movement)
(@CGUID+710, 49541, 36, 1, 1, -79.44965, -819.8351, 39.89838, 0.01745329, 7200, 0, 0), -- Vanessa VanCleef (Area: 0) (possible waypoints or random movement)
(@CGUID+711, 45979, 36, 1, 1, -38.11458, -795.2952, 39.45137, 3.926991, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+712, 45979, 36, 1, 1, -64.02257, -797.4323, 39.12309, 3.926991, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+713, 45979, 36, 1, 1, -46.48438, -791.8073, 39.12098, 3.926991, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+714, 45979, 36, 1, 1, -75.50694, -787.1597, 39.16325, 3.926991, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+715, 45979, 36, 1, 1, -66.18229, -789.2778, 39.78834, 3.926991, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+716, 45979, 36, 1, 1, -70.9809, -795.5, 39.14447, 3.926991, 7200, 0, 0), -- General Purpose Bunny JMF (Area: 0)
(@CGUID+717, 51594, 36, 1, 1, -85.18403, -822.6042, 39.48589, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+718, 51594, 36, 1, 1, -62.18924, -834.6563, 41.49004, 3.193953, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+719, 51594, 36, 1, 1, -76.88889, -806.1927, 40.12347, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+720, 51594, 36, 1, 1, -60.28472, -806.1979, 41.61631, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+721, 51594, 36, 1, 1, -41.65799, -834.1059, 34.51352, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+722, 51594, 36, 1, 1, -79.61111, -794.7726, 38.50275, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+723, 51594, 36, 1, 1, -54.19097, -789.9566, 38.85344, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+724, 51594, 36, 1, 1, -59.27778, -787.6597, 39.37201, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+725, 51594, 36, 1, 1, -44.94792, -801.1077, 40.703, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+726, 51594, 36, 1, 1, -75.33681, -833.434, 40.29444, 3.193953, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+727, 51594, 36, 1, 1, -62.4375, -825.9114, 41.42738, 3.193953, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+728, 51594, 36, 1, 1, -70.38889, -824.9722, 40.70635, 3.193953, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+729, 51594, 36, 1, 1, -66.54514, -815.118, 41.0335, 3.193953, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+730, 51594, 36, 1, 1, -57.90972, -816.8611, 41.85588, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+731, 51594, 36, 1, 1, -54.5382, -833.9739, 42.20368, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+732, 51594, 36, 1, 1, -81.48264, -832.3143, 39.79344, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+733, 51594, 36, 1, 1, -76.38541, -821.6371, 40.15092, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+734, 51594, 36, 1, 1, -84.03125, -817.4323, 39.54358, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+735, 51594, 36, 1, 1, -34.31597, -825.7864, 35.14482, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+736, 51594, 36, 1, 1, -101.6024, -822.2257, 38.22025, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+737, 51594, 36, 1, 1, -110, -821.908, 30.27846, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+738, 51594, 36, 1, 1, -54.32118, -840.3108, 33.4867, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+739, 51594, 36, 1, 1, -92.3125, -835.5712, 31.01794, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+740, 51594, 36, 1, 1, -95.20313, -826.7986, 38.69661, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+741, 51594, 36, 1, 1, -81.6875, -791.7795, 25.86889, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+742, 51594, 36, 1, 1, -75.52952, -788.3438, 26.0653, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+743, 51594, 36, 1, 1, -104.3299, -806.0121, 30.58083, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+744, 51594, 36, 1, 1, -87.6875, -830.8108, 39.29154, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+745, 51594, 36, 1, 1, -46.73611, -821.1771, 52.5815, 3.193953, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+746, 51594, 36, 1, 1, -69.06944, -834.368, 40.86119, 3.193953, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+747, 51594, 36, 1, 1, -68.94444, -805.1528, 40.82362, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+748, 51594, 36, 1, 1, -38.67708, -816.1389, 43.68202, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+749, 51594, 36, 1, 1, -46.09722, -830.2518, 43.00029, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+750, 51594, 36, 1, 1, -46.44965, -809.7448, 42.93429, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+751, 51594, 36, 1, 1, -54.49479, -826.5833, 42.19642, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+752, 51594, 36, 1, 1, -37.77257, -824.493, 43.78171, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+753, 51594, 36, 1, 1, -106.7882, -827.8351, 30.3655, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+754, 51594, 36, 1, 1, -85.05209, -808.5243, 39.47224, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+755, 51594, 36, 1, 1, -108.5208, -840.7136, 17.11709, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+756, 51594, 36, 1, 1, -74, -813.632, 40.37197, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+757, 51594, 36, 1, 1, -101.724, -815.1875, 38.20302, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+758, 51594, 36, 1, 1, -109.6736, -832.7049, 20.99191, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+759, 51594, 36, 1, 1, -93.49653, -809.6979, 38.80095, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+760, 51594, 36, 1, 1, -92.09202, -843.8507, 21.32712, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+761, 51594, 36, 1, 1, -82.74479, -853.8368, 17.44633, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+762, 51594, 36, 1, 1, -83.51563, -847.0851, 18.62521, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+763, 51594, 36, 1, 1, -77.3316, -848.7101, 16.88625, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+764, 51594, 36, 1, 1, -47.97917, -851.7882, 18.46356, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+765, 51594, 36, 1, 1, -54.41667, -846.2222, 22.62641, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+766, 51594, 36, 1, 1, -46.15799, -843.5104, 23.03055, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+767, 51594, 36, 1, 1, -32.24479, -844.8195, 19.15213, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+768, 51594, 36, 1, 1, -28.87847, -840.0226, 19.30344, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+769, 51594, 36, 1, 1, -31.54861, -830.5191, 23.84564, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+770, 51594, 36, 1, 1, -53.39583, -808.4184, 42.27031, 2.75762, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+771, 51594, 36, 1, 1, -59.65799, -786.8472, 18.00813, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+772, 49550, 36, 1, 1, -67.79166, -840.1736, 40.96664, 4.712389, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+773, 49550, 36, 1, 1, -70.62153, -840.0104, 40.71846, 4.537856, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+774, 49550, 36, 1, 1, -64.97049, -840.0087, 41.22668, 4.834562, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+775, 51594, 36, 1, 1, -51.8559, -788.4774, 18.27221, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+776, 49550, 36, 1, 1, -73.42361, -839.8646, 40.47259, 4.34587, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+777, 49550, 36, 1, 1, -62.17014, -839.8438, 41.48514, 5.044002, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+778, 51594, 36, 1, 1, -115.3142, -827.2327, 20.94427, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+779, 51594, 36, 1, 1, -116.1042, -835.6597, 17.07181, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+780, 51594, 36, 1, 1, -17.43924, -821.8785, 19.89213, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+781, 51594, 36, 1, 1, -22.3125, -807.7292, 19.61356, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+782, 51594, 36, 1, 1, -17.77431, -814.7327, 19.87694, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+783, 51594, 36, 1, 1, -116.9809, -803.1337, 17.05497, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+784, 51594, 36, 1, 1, -122.8872, -816.658, 17.01834, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+785, 51594, 36, 1, 1, -65.53993, -768.6545, 28.01228, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+786, 51594, 36, 1, 1, -123.3351, -807.2153, 16.98381, 3.926991, 7200, 0, 0), -- Glubtok Nightmare Fire Bunny (Area: 0)
(@CGUID+787, 49550, 36, 1, 1, -73.42361, -839.8646, 40.47259, 4.34587, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+788, 49550, 36, 1, 1, -70.62153, -840.0104, 40.71846, 4.537856, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+789, 49550, 36, 1, 1, -67.79166, -840.1736, 40.96664, 4.712389, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+790, 49550, 36, 1, 1, -64.97049, -840.0087, 41.22668, 4.834562, 7200, 0, 0), -- Rope (Area: 0)
(@CGUID+791, 49550, 36, 1, 1, -62.17014, -839.8438, 41.48514, 5.044002, 7200, 0, 0); -- Rope (Area: 0)
UPDATE `creature` SET `phaseMask`= 64 WHERE `id` IN (49494, 49671, 49670, 51594, 49495, 49493, 49493, 49674, 49520, 49681, 49682, 49534, 49532, 49535, 49539) AND `map`= 36;
UPDATE `creature` SET `spawnMask`= 3 WHERE `map`= 36;
UPDATE `gameobject` SET `spawnMask`= 3 WHERE `map`= 36;
﻿UPDATE `creature_template` SET `difficulty_entry_1`=48834 WHERE `entry`= 48229;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `baseattacktime`=1000, `unit_flags`=64, `exp`=3 WHERE `entry`=48834; -- Kobold Digger
UPDATE `creature_template` SET `difficulty_entry_1`=48829 WHERE `entry`= 48230;
UPDATE `creature_template` SET `minlevel`=86, `maxlevel`=86, `exp`=3 WHERE `entry`=48829; -- Ogre Henchman
UPDATE `creature_template` SET `difficulty_entry_1`=48913 WHERE `entry`= 48266;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `unit_flags`=33554432, `exp`=3 WHERE `entry`=48913; -- Defias Cannon
UPDATE `creature_template` SET `difficulty_entry_1`=48936 WHERE `entry`= 47162;
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `npcflag`=0, `exp`=3 WHERE `entry`=48936; -- Glubtok
UPDATE `creature_template` SET `difficulty_entry_1`=48820 WHERE `entry`= 48338;
UPDATE `creature_template` SET `difficulty_entry_1`=48821 WHERE `entry`= 48351;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48821; -- Mine Bunny
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48820; -- Mine Bunny
UPDATE `creature_template` SET `difficulty_entry_1`=48804 WHERE `entry`= 47403;
UPDATE `creature_template` SET `minlevel`=86, `maxlevel`=86, `exp`=3 WHERE `entry`=48804; -- Defias Reaper
UPDATE `creature_template` SET `difficulty_entry_1`=48803 WHERE `entry`= 47404;
UPDATE `creature_template` SET `minlevel`=86, `maxlevel`=86, `exp`=3 WHERE `entry`=48803; -- Defias Watcher
UPDATE `creature_template` SET `difficulty_entry_1`=48939 WHERE `entry`= 47297;
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `exp`=3 WHERE `entry`=48939; -- Lumbering Oaf
UPDATE `creature_template` SET `difficulty_entry_1`=48940 WHERE `entry`= 47296;
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `npcflag`=0, `exp`=3 WHERE `entry`=48940; -- Helix Gearbreaker
UPDATE `creature_template` SET `difficulty_entry_1`=48830 WHERE `entry`= 48262;
UPDATE `creature_template` SET `minlevel`=86, `maxlevel`=86, `exp`=3 WHERE `entry`=48830; -- Ogre Bodyguard
UPDATE `creature_template` SET `difficulty_entry_1`=48941 WHERE `entry`= 43778;
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `npcflag`=0, `exp`=3 WHERE `entry`=48941; -- Foe Reaper 5000
UPDATE `creature_template` SET `difficulty_entry_1`=48826 WHERE `entry`= 48441;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48826; -- Mining Monkey
UPDATE `creature_template` SET `difficulty_entry_1`=48823 WHERE `entry`= 48278;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48823; -- Mining Monkey
UPDATE `creature_template` SET `difficulty_entry_1`=48827 WHERE `entry`= 48441;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48827; -- Mining Monkey
UPDATE `creature_template` SET `difficulty_entry_1`=48824 WHERE `entry`= 48440;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48824; -- Mining Monkey
UPDATE `creature_template` SET `difficulty_entry_1`=48819 WHERE `entry`= 48279;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48819; -- Goblin Overseer
UPDATE `creature_template` SET `difficulty_entry_1`=48814 WHERE `entry`= 48445;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `baseattacktime`=3000, `exp`=3 WHERE `entry`=48814; -- Oaf Lackey
UPDATE `creature_template` SET `difficulty_entry_1`=48787 WHERE `entry`= 48502;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48787; -- Defias Enforcer
UPDATE `creature_template` SET `difficulty_entry_1`=48791 WHERE `entry`= 48417;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48791; -- Defias Blood Wizard
UPDATE `creature_template` SET `difficulty_entry_1`=48810 WHERE `entry`= 48420;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `unit_flags`=32832, `exp`=3 WHERE `entry`=48810; -- Defias Digger
UPDATE `creature_template` SET `difficulty_entry_1`=48811 WHERE `entry`= 48419;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `unit_flags`=64, `exp`=3 WHERE `entry`=48811; -- Defias Miner
UPDATE `creature_template` SET `difficulty_entry_1`=48812 WHERE `entry`= 48418;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48812; -- Defias Envoker
UPDATE `creature_template` SET `difficulty_entry_1`=48914 WHERE `entry`= 48421;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48914; -- Defias Overseer
UPDATE `creature_template` SET `difficulty_entry_1`=48791 WHERE `entry`= 48505;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48791; -- Defias Shadowguard
UPDATE `creature_template` SET `difficulty_entry_1`=48781 WHERE `entry`= 48447;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `unit_flags`=64, `exp`=3 WHERE `entry`=48781; -- Monstrous Parrot
UPDATE `creature_template` SET `difficulty_entry_1`=48782 WHERE `entry`= 48450;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `unit_flags`=64, `exp`=3 WHERE `entry`=48782; -- Sunwing Squawker
UPDATE `creature_template` SET `difficulty_entry_1`=48943 WHERE `entry`= 47626;
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `npcflag`=0, `exp`=3 WHERE `entry`=48943; -- Admiral Ripsnarl
UPDATE `creature_template` SET `difficulty_entry_1`=48779 WHERE `entry`= 48451;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `unit_flags`=64, `exp`=3 WHERE `entry`=48779; -- Ol' Beaky
UPDATE `creature_template` SET `difficulty_entry_1`=48777 WHERE `entry`= 48522;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48777; -- Defias Pirate
UPDATE `creature_template` SET `difficulty_entry_1`=48778 WHERE `entry`= 48521;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3 WHERE `entry`=48778; -- Defias Squallshaper
UPDATE `creature_template` SET `difficulty_entry_1`=48944 WHERE `entry`= 47739;
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `npcflag`=0, `exp`=3 WHERE `entry`=48944; -- "Captain" Cookie
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `faction_A`=2263, `faction_H`=2263, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_flags2`=0 WHERE `entry`=49535; -- Erik Harrington
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `faction_A`=14, `faction_H`=14, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_flags`=32832, `unit_flags2`=0, `VehicleId`=1403 WHERE `entry`=49539; -- James Harrington
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `faction_A`=2263, `faction_H`=2263, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_flags2`=0 WHERE `entry`=49536; -- Calissa Harrington
UPDATE `creature_template` SET `exp`=3 WHERE `entry` IN (SELECT `id` FROM `creature` WHERE `map`= 36);
﻿/*
18:52:23.174 -- aggro
70889 -- notiz
18:52:41.348 -- blink 1: 18 seconds
18:52:54.608 -- blink 2: 13 seconds
18:53:06.261 -- teleport
18:53:10.083 -- ready ?
18:53:12.486
18:53:14.888 -- arkane macht cast
18:53:18.523
18:53:20.707 -- blossom targeting
18:53:23.109 -- fire blossom 
*/
-- Glubtok Encounter
UPDATE `creature_template` SET `scriptname`= 'boss_glubtok', `exp`= 3 WHERE `entry`= 47162;
UPDATE `creature_template` SET `scriptname`= 'npc_dm_firewall_rotator'  WHERE `entry`= 48974;
DELETE FROM conditions WHERE SourceEntry IN (88072, 88093, 88140);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 88072, 0, 0, 31, 0, 3, 47162, 0, 0, 0, '', 'Glubtok - Firebeam Target Glubtok'),
(13, 1, 88093, 0, 0, 31, 0, 3, 47162, 0, 0, 0, '', 'Glubtok - Frostbeam Target Glubtok'),
(13, 1, 88140, 0, 0, 31, 0, 3, 47282, 0, 0, 0, '', 'Glubtok - Blossom Targeting'),
(13, 2, 88140, 0, 0, 31, 0, 3, 47284, 0, 0, 0, '', 'Glubtok - Blossom Targeting');
DELETE FROM `creature_text` WHERE `entry`= 47162;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(47162, 0, 0, 'Glubtok zeigt Euch arkane Macht', 14, 0, 100, 0, 0, 21151, 'Glubtok'),
(47162, 2, 0, 'Flammenfäuste', 14, 0, 100, 0, 0, 21153, 'Glubtok'),
(47162, 1, 0, 'Frostfäuste', 14, 0, 100, 0, 0, 21156, 'Glubtok'),
(47162, 3, 0, 'Glubtok bereit?', 14, 0, 100, 1, 0, 21154, 'Glubtok'),
(47162, 4, 0, 'Los geht''s', 14, 0, 100, 15, 0, 21157, 'Glubtok'),
(47162, 5, 0, 'ARKANE MACHT', 14, 0, 100, 15, 0, 21146, 'Glubtok'),
(47162, 6, 0, '|TInterface\\Icons\\spell_holy_innerfire.blp:20|t Glubtok erschafft eine sich bewegende |cFFFF0000|Hspell:91398|h''Feuerwand''|h|r', 41, 0, 100, 0, 0, 0, 'Glubtok'),
(47162, 7, 0, 'ZU... VIEL... MACHT', 14, 0, 100, 15, 0, 21145, 'Glubtok');
DELETE FROM `creature_template_addon` WHERE `entry` IN (48974, 48975, 49039, 49040, 48976, 49041, 49042);
-- DB Stuff for Helix encounter
UPDATE `creature_template` SET `scriptname`= 'boss_helix_gearbreaker' WHERE `entry`= 47296;
UPDATE `creature_template` SET `scriptname`= 'npc_lumbering_oaf' WHERE `entry`= 47297;
UPDATE `creature_template` SET `scriptname`= 'npc_helix_crew' WHERE `entry`= 49139;
UPDATE `creature_template` SET `scriptname`= 'npc_sticky_bomb', `minlevel`= 85, `maxlevel`= 85 WHERE `entry`= 47314;
-- manually spawn helix
DELETE FROM `creature` WHERE `guid` = 785575;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(785575, 47296, 36, 4294967295, 1, -305.148102, -516.838989, 53.218662, 0.151292, 300, 100000000, 34797);
DELETE FROM `creature_text` WHERE `entry` IN (47296, 49136, 47297);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(47296, 0, 0, 'Die Herrin entlohnt mich gut für Eure Köpfe', 14, 0, 100, 0, 0, 20849, 'Helix Ritzelbrecher'),
(47296, 1, 0, 'Feuer frei', 14, 0, 100, 0, 0, 20847, 'Helix Ritzelbrecher'),
(47296, 1, 1, 'Fertig, Trampel? Wirf', 14, 0, 100, 0, 0, 20848, 'Helix Ritzelbrecher'),
(47296, 2, 0, 'Helix befestigt eine Bombe an der Brust von $N', 41, 0, 100, 0, 0, 0, 'Helix Ritzelbrecher'),
(47296, 3, 0, 'Ich brauch ihn nicht, ich hab ja EUCH Trampel', 14, 0, 100, 0, 0, 20846, 'Helix Ritzelbrecher to Trampel'),
(49136, 0, 0, 'Sie werden in Stücke geschossen, Boss', 12, 0, 100, 0, 0, 0, 'Helix'' Besatzungsmitglied'),
(47297, 0, 0, 'Nein…NEIN', 14, 0, 100, 0, 0, 20854, 'Trampel to Helix Ritzelbrecher'),
(47297, 1, 0, 'TRAMPEL ZERQUETSCHT', 14, 0, 100, 0, 0, 0, 'Trampel to Helix Ritzelbrecher');
DELETE FROM `spell_script_names` WHERE `spell_id` IN (88352);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88352, 'spell_dm_chest_bomb');
DELETE FROM `spell_proc_event` WHERE `entry` = '78228';
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (78228, 0, 6, 8421376, 1024, 0, 0, 2, 0, 0, 0);
UPDATE `spell_proc_event` SET `procEx`=2 WHERE `entry`=33191 LIMIT 1;
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_pri_power_word_shield';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (17, 'spell_pri_power_word_shield');
﻿
/*
Author : Northstrider
Descr. : druid efflorescence
Ticket :
*/
DELETE FROM `spell_script_names` WHERE `spell_id` = 81262;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(81262,'spell_dru_efflorescence');
DELETE FROM `spell_proc_event` WHERE `entry` IN (34151, 81274, 81275);
INSERT INTO `spell_proc_event` (`entry`, `SpellFamilyName`, `SpellFamilyMask1`) VALUES
('34151','7','2'),
('81274','7','2'),
('81275','7','2');
DELETE FROM `spell_script_names` WHERE `spell_id` = '586';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (586, 'spell_pri_fade');
## Archangel (Evangelism & Dark Evangelism#
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-87118 AND `spell_effect`=-87154 AND `type`=0 LIMIT 1;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-87117 AND `spell_effect`=-87154 AND `type`=0 LIMIT 1;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-87117 AND `spell_effect`=-94709 AND `type`=0 LIMIT 1;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-87118 AND `spell_effect`=-94709 AND `type`=0 LIMIT 1;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-81660 AND `spell_effect`=-87154 AND `type`=0 LIMIT 1;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-81661 AND `spell_effect`=-87154 AND `type`=0 LIMIT 1;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-81660 AND `spell_effect`=-94709 AND `type`=0 LIMIT 1;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-81661 AND `spell_effect`=-94709 AND `type`=0 LIMIT 1;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-87118, -87154, 0, 'Dark Evangelism -> Remove Archangel Trigger');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-87117, -87154, 0, 'Dark Evangelism -> Remove Archangel Trigger');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-87117, -94709, 0, 'Dark Evangelism -> Remove Archangel');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-87118, -94709, 0, 'Dark Evangelism -> Remove Archangel');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81660, -87154, 0, 'Evangelism -> Remove Archangel Trigger');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81661, -87154, 0, 'Evangelism -> Remove Archangel Trigger');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81660, -94709, 0, 'Evangelism -> Remove Archangel');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81661, -94709, 0, 'Evangelism -> Remove Archangel');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-77487';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-77487, -93683, 0, 'Shadow Orbs -> Remove Marker');
DELETE FROM `spell_proc_event` WHERE entry IN (87099, 87100);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(87099, 0, 0, 0, 0, 1088, 0, 0, 0, 0, 0), -- Sin and Punishment (Rank 1)
(87100, 0, 0, 0, 0, 1088, 0, 0, 0, 0, 0); -- Sin and Punishment (Rank 2)
﻿
REPLACE INTO `item_enchantment_template` VALUES 
('61', '6', '7.73'),
('61', '8', '7.31'),
('61', '9', '8.02'),
('61', '15', '3.01'),
('61', '16', '3.39'),
('61', '19', '3.74'),
('61', '21', '0.9'),
('61', '22', '1.01'),
('61', '23', '0.95'),
('61', '25', '0.82'),
('61', '26', '0.98'),
('61', '31', '1.69'),
('61', '32', '2.12'),
('61', '33', '1.79'),
('61', '34', '1.84'),
('61', '35', '1.8'),
('61', '36', '14.32'),
('61', '37', '10.77'),
('61', '38', '10.6'),
('61', '39', '17.48'),
('63', '5', '3.09'),
('63', '6', '3.32'),
('63', '7', '3.46'),
('63', '8', '2.84'),
('63', '9', '2.86'),
('63', '10', '3.5'),
('63', '11', '3.34'),
('63', '12', '2.81'),
('63', '13', '2.88'),
('63', '14', '3.41'),
('63', '15', '1.13'),
('63', '16', '1.33'),
('63', '17', '1.55'),
('63', '18', '1.62'),
('63', '19', '1.36'),
('63', '21', '0.91'),
('63', '24', '0.97'),
('63', '26', '1.08'),
('63', '27', '0.92'),
('63', '31', '1.44'),
('63', '32', '1.82'),
('63', '33', '1.61'),
('63', '34', '1.49'),
('63', '35', '1.46'),
('63', '39', '8.03'),
('63', '40', '27.31'),
('63', '41', '7.03'),
('63', '42', '8.02'),
('64', '5', '2.8'),
('64', '6', '3.07'),
('64', '7', '3.5'),
('64', '8', '3.04'),
('64', '9', '3.16'),
('64', '10', '3.41'),
('64', '11', '2.74'),
('64', '12', '3.08'),
('64', '13', '2.69'),
('64', '14', '3.4'),
('64', '15', '1.25'),
('64', '16', '1.49'),
('64', '17', '1.66'),
('64', '18', '1.42'),
('64', '19', '1.43'),
('64', '24', '1.32'),
('64', '26', '1.53'),
('64', '27', '1.31'),
('64', '31', '2.1'),
('64', '32', '2.3'),
('64', '33', '1.93'),
('64', '34', '1.7'),
('64', '35', '1.78'),
('64', '39', '10.09'),
('64', '40', '19.63'),
('64', '43', '9.12'),
('64', '44', '9.72'),
('65', '5', '2.99'),
('65', '6', '3.32'),
('65', '7', '2.49'),
('65', '8', '3.08'),
('65', '9', '3.45'),
('65', '10', '3.66'),
('65', '11', '3.6'),
('65', '12', '3.21'),
('65', '13', '3.23'),
('65', '14', '3.46'),
('65', '15', '1.37'),
('65', '16', '1.37'),
('65', '17', '1.69'),
('65', '18', '1.84'),
('65', '19', '1.57'),
('65', '26', '2.32'),
('65', '27', '2.32'),
('65', '31', '1.89'),
('65', '32', '1.97'),
('65', '33', '1.86'),
('65', '34', '2.17'),
('65', '35', '1.71'),
('65', '36', '10.06'),
('65', '41', '10.92'),
('65', '44', '11.82'),
('65', '45', '13.08'),
('66', '5', '3.19'),
('66', '6', '2.29'),
('66', '7', '3.16'),
('66', '8', '2.6'),
('66', '9', '2.91'),
('66', '10', '3.52'),
('66', '11', '3.17'),
('66', '12', '3.58'),
('66', '13', '3.19'),
('66', '14', '3.83'),
('66', '15', '1.4'),
('66', '16', '1.15'),
('66', '17', '1.99'),
('66', '18', '1.95'),
('66', '19', '1.35'),
('66', '21', '0.79'),
('66', '22', '0.9'),
('66', '23', '0.79'),
('66', '24', '0.7'),
('66', '25', '0.6'),
('66', '26', '0.75'),
('66', '27', '0.73'),
('66', '31', '1.65'),
('66', '32', '1.98'),
('66', '33', '1.66'),
('66', '34', '1.79'),
('66', '35', '1.51'),
('66', '36', '4.36'),
('66', '37', '1.89'),
('66', '38', '2.23'),
('66', '39', '6.37'),
('66', '40', '13.99'),
('66', '41', '5.51'),
('66', '42', '2.13'),
('66', '43', '2.09'),
('66', '44', '4.21'),
('66', '45', '4.05'),
('81', '5', '2.91'),
('81', '6', '2.74'),
('81', '7', '2.98'),
('81', '8', '2.98'),
('81', '9', '3.36'),
('81', '10', '3.64'),
('81', '11', '3.19'),
('81', '12', '3.25'),
('81', '13', '3.17'),
('81', '14', '3.68'),
('81', '15', '1.39'),
('81', '16', '1.24'),
('81', '17', '1.87'),
('81', '18', '1.65'),
('81', '19', '1.56'),
('81', '28', '1.45'),
('81', '29', '3.93'),
('81', '30', '1.65'),
('81', '31', '1.55'),
('81', '32', '1.94'),
('81', '33', '1.76'),
('81', '34', '1.73'),
('81', '35', '1.59'),
('81', '36', '5'),
('81', '37', '2.34'),
('81', '38', '2.59'),
('81', '39', '7.28'),
('81', '40', '10.15'),
('81', '41', '4.64'),
('81', '42', '2.4'),
('81', '43', '1.77'),
('81', '44', '4.95'),
('81', '45', '3.66'),
('82', '5', '3.02'),
('82', '6', '2.8'),
('82', '7', '2.52'),
('82', '8', '3.04'),
('82', '9', '3.3'),
('82', '10', '3.55'),
('82', '11', '3.53'),
('82', '12', '3.42'),
('82', '13', '3.31'),
('82', '14', '3.49'),
('82', '15', '1.49'),
('82', '16', '1.31'),
('82', '17', '1.69'),
('82', '18', '1.7'),
('82', '19', '1.58'),
('82', '24', '1.15'),
('82', '26', '1.04'),
('82', '27', '1.14'),
('82', '31', '1.94'),
('82', '32', '1.89'),
('82', '33', '1.84'),
('82', '34', '1.79'),
('82', '35', '1.85'),
('82', '36', '5.63'),
('82', '39', '5.21'),
('82', '41', '8.78'),
('82', '43', '5.09'),
('82', '44', '11.81'),
('82', '45', '8.77'),
('82', '47', '2.32'),
('83', '6', '7.41'),
('83', '8', '8.74'),
('83', '9', '8.84'),
('83', '15', '4.2'),
('83', '16', '4.12'),
('83', '19', '4.16'),
('83', '21', '1.07'),
('83', '22', '1.08'),
('83', '23', '1.05'),
('83', '24', '0.98'),
('83', '25', '0.77'),
('83', '26', '0.81'),
('83', '31', '2.26'),
('83', '32', '2.49'),
('83', '33', '2.45'),
('83', '34', '2.48'),
('83', '35', '2.19'),
('83', '36', '8.84'),
('83', '37', '6.98'),
('83', '38', '7.11'),
('83', '39', '15.31'),
('83', '42', '6.69'),
('84', '6', '12.23'),
('84', '8', '12.25'),
('84', '9', '12.64'),
('84', '15', '5.83'),
('84', '16', '6.22'),
('84', '19', '6.29'),
('84', '44', '44.51'),
('85', '7', '17.67'),
('85', '14', '17.89'),
('85', '16', '8.57'),
('85', '17', '8.84'),
('85', '41', '47.03'),
('86', '5', '3.89'),
('86', '6', '4.81'),
('86', '7', '3.98'),
('86', '8', '4.18'),
('86', '9', '4.54'),
('86', '10', '4.21'),
('86', '11', '3.94'),
('86', '12', '3.84'),
('86', '13', '3.69'),
('86', '14', '4.23'),
('86', '15', '1.85'),
('86', '16', '1.92'),
('86', '17', '2.06'),
('86', '18', '2.03'),
('86', '19', '2.44'),
('86', '39', '5.46'),
('86', '40', '20.54'),
('86', '41', '6.58'),
('86', '43', '3.62'),
('86', '44', '4.75'),
('86', '45', '7.41'),
('87', '5', '3.81'),
('87', '6', '4.34'),
('87', '7', '3.6'),
('87', '8', '3.95'),
('87', '9', '4.51'),
('87', '10', '4.21'),
('87', '11', '4.21'),
('87', '12', '3.8'),
('87', '13', '4.01'),
('87', '14', '3.87'),
('87', '15', '1.81'),
('87', '16', '1.81'),
('87', '17', '1.89'),
('87', '18', '1.95'),
('87', '19', '2.16'),
('87', '36', '5.14'),
('87', '39', '4.56'),
('87', '40', '12.84'),
('87', '41', '6.34'),
('87', '43', '3.63'),
('87', '44', '10.15'),
('87', '45', '7.37'),
('88', '5', '4.33'),
('88', '6', '4.11'),
('88', '7', '4.24'),
('88', '8', '3.61'),
('88', '9', '3.71'),
('88', '10', '3.84'),
('88', '11', '3.81'),
('88', '12', '3.48'),
('88', '13', '3.54'),
('88', '14', '4.39'),
('88', '15', '1.44'),
('88', '16', '1.97'),
('88', '17', '2.01'),
('88', '18', '1.9'),
('88', '19', '1.81'),
('88', '36', '7.07'),
('88', '39', '5.9'),
('88', '41', '10.33'),
('88', '43', '6.12'),
('88', '44', '12.21'),
('88', '45', '10.22'),
('89', '5', '3.59'),
('89', '6', '5.04'),
('89', '7', '3.84'),
('89', '8', '4.06'),
('89', '9', '4.94'),
('89', '10', '4.82'),
('89', '11', '4.61'),
('89', '12', '4.18'),
('89', '13', '3.91'),
('89', '14', '3.88'),
('89', '15', '1.92'),
('89', '16', '1.77'),
('89', '17', '2.05'),
('89', '18', '1.88'),
('89', '19', '2.52'),
('89', '36', '6.37'),
('89', '40', '20.61'),
('89', '41', '5.98'),
('89', '44', '6.1'),
('89', '45', '7.94'),
('90', '5', '4.04'),
('90', '6', '4.37'),
('90', '7', '4.31'),
('90', '8', '3.58'),
('90', '9', '3.74'),
('90', '10', '4.19'),
('90', '11', '3.82'),
('90', '12', '3.63'),
('90', '13', '3.62'),
('90', '14', '4.52'),
('90', '15', '1.41'),
('90', '16', '2.04'),
('90', '17', '2.09'),
('90', '18', '2.04'),
('90', '19', '1.88'),
('90', '36', '7.34'),
('90', '40', '15.52'),
('90', '41', '10.16'),
('90', '44', '6.93'),
('90', '45', '10.82'),
('91', '5', '4.15'),
('91', '6', '3.73'),
('91', '7', '4.41'),
('91', '8', '3.55'),
('91', '9', '3.58'),
('91', '10', '3.85'),
('91', '11', '3.73'),
('91', '12', '3.58'),
('91', '13', '3.58'),
('91', '14', '4.28'),
('91', '15', '1.46'),
('91', '16', '1.64'),
('91', '17', '1.72'),
('91', '18', '1.82'),
('91', '19', '1.82'),
('91', '39', '5.37'),
('91', '40', '16.3'),
('91', '41', '10.75'),
('91', '43', '5.56'),
('91', '44', '5.12'),
('91', '45', '9.92'),
('92', '5', '3.98'),
('92', '6', '4.21'),
('92', '7', '3.96'),
('92', '8', '3.86'),
('92', '9', '4.13'),
('92', '10', '4.09'),
('92', '11', '4.01'),
('92', '12', '3.89'),
('92', '13', '3.75'),
('92', '14', '4.12'),
('92', '15', '1.71'),
('92', '16', '1.94'),
('92', '17', '2.04'),
('92', '18', '2.09'),
('92', '19', '2.05'),
('92', '36', '5.58'),
('92', '39', '4.82'),
('92', '40', '10.92'),
('92', '41', '6.84'),
('92', '43', '4.06'),
('92', '44', '10.16'),
('92', '45', '7.84'),
('93', '5', '4.11'),
('93', '6', '4.29'),
('93', '7', '4.04'),
('93', '8', '4.11'),
('93', '9', '4.12'),
('93', '10', '4.36'),
('93', '11', '4.24'),
('93', '12', '4.1'),
('93', '13', '3.91'),
('93', '14', '4.25'),
('93', '15', '1.81'),
('93', '16', '1.91'),
('93', '17', '2.1'),
('93', '18', '2.13'),
('93', '19', '2.06'),
('93', '39', '4.79'),
('93', '40', '21.55'),
('93', '41', '6.58'),
('93', '43', '3.69'),
('93', '44', '4.33'),
('93', '45', '7.49'),
('94', '5', '4.16'),
('94', '6', '4.32'),
('94', '7', '4.59'),
('94', '8', '3.91'),
('94', '9', '3.86'),
('94', '10', '3.95'),
('94', '11', '4'),
('94', '12', '3.83'),
('94', '13', '3.78'),
('94', '14', '4.74'),
('94', '15', '1.58'),
('94', '16', '2.04'),
('94', '17', '2.13'),
('94', '18', '2.07'),
('94', '19', '1.84'),
('94', '36', '2.99'),
('94', '40', '22.18'),
('94', '41', '15.06'),
('94', '44', '4.78'),
('94', '45', '4.27'),
('95', '5', '3.75'),
('95', '6', '4.45'),
('95', '7', '4.52'),
('95', '8', '3.69'),
('95', '9', '4.18'),
('95', '10', '4.14'),
('95', '11', '3.96'),
('95', '12', '4.15'),
('95', '13', '3.99'),
('95', '14', '4.54'),
('95', '15', '1.86'),
('95', '16', '1.76'),
('95', '17', '2.41'),
('95', '18', '2.1'),
('95', '19', '1.94'),
('95', '40', '30.48'),
('95', '41', '8.33'),
('95', '45', '9.74'),
('96', '6', '8.08'),
('96', '8', '7.96'),
('96', '9', '8.19'),
('96', '15', '3.6'),
('96', '16', '4.06'),
('96', '19', '4.22'),
('96', '21', '2.11'),
('96', '22', '2.28'),
('96', '23', '2.27'),
('96', '25', '1.8'),
('96', '26', '2.35'),
('96', '36', '14.74'),
('96', '37', '11.18'),
('96', '38', '10.86'),
('96', '39', '16.34'),
('141', '51', '30.8'),
('141', '53', '32.75'),
('141', '55', '36.4'),
('142', '49', '51.65'),
('142', '57', '48.35'),
('143', '50', '44.1'),
('143', '54', '55.9'),
('144', '52', '60.55'),
('144', '56', '39.45'),
('161', '58', '48.65'),
('161', '59', '51.35'),
('162', '58', '51.35'),
('162', '60', '48.65'),
('163', '58', '55.4'),
('163', '60', '44.6'),
('456', '15', '1.48'),
('456', '19', '1.48'),
('456', '22', '1.48'),
('456', '94', '4.35'),
('456', '95', '4.72'),
('456', '96', '2.41'),
('456', '112', '4.35'),
('456', '113', '4.72'),
('456', '114', '2.41'),
('456', '197', '0.1'),
('456', '757', '5.79'),
('456', '758', '5.79'),
('456', '759', '5.79'),
('456', '760', '5.79'),
('456', '842', '3.9'),
('456', '843', '3.9'),
('456', '844', '3.9'),
('456', '845', '3.9'),
('456', '1012', '4.4'),
('456', '1013', '4.4'),
('456', '1014', '4.4'),
('456', '1015', '4.4'),
('456', '1307', '0.1'),
('456', '1802', '3.48'),
('456', '1803', '3.48'),
('456', '1840', '2.42'),
('456', '1841', '2.42'),
('456', '1954', '3.33'),
('456', '1955', '3.33'),
('457', '14', '0.1'),
('457', '29', '0.1'),
('457', '133', '4.56'),
('457', '134', '4.97'),
('457', '135', '3.51'),
('457', '152', '4.56'),
('457', '153', '4.97'),
('457', '154', '3.51'),
('457', '506', '0.1'),
('457', '510', '0.1'),
('457', '760', '5.82'),
('457', '761', '5.82'),
('457', '762', '5.82'),
('457', '763', '5.82'),
('457', '845', '3.84'),
('457', '846', '3.84'),
('457', '847', '3.84'),
('457', '848', '3.84'),
('457', '1015', '4.49'),
('457', '1016', '4.49'),
('457', '1017', '4.49'),
('457', '1018', '4.49'),
('457', '1804', '3.25'),
('457', '1805', '3.25'),
('457', '1842', '2.1'),
('457', '1843', '2.1'),
('457', '1956', '3.24'),
('457', '1957', '3.24'),
('458', '31', '0.1'),
('458', '152', '4.44'),
('458', '153', '5.24'),
('458', '154', '3.4'),
('458', '174', '4.44'),
('458', '179', '5.24'),
('458', '184', '3.4'),
('458', '683', '0.1'),
('458', '763', '6.15'),
('458', '764', '6.15'),
('458', '765', '6.15'),
('458', '766', '6.15'),
('458', '848', '3.32'),
('458', '849', '3.32'),
('458', '850', '3.32'),
('458', '851', '3.32'),
('458', '1018', '4.41'),
('458', '1019', '4.41'),
('458', '1020', '4.41'),
('458', '1021', '4.41'),
('458', '1022', '3.58'),
('458', '1805', '3.4'),
('458', '1806', '3.4'),
('458', '1843', '2.11'),
('458', '1844', '2.11'),
('458', '1957', '3.2'),
('458', '1958', '3.2'),
('459', '175', '4.62'),
('459', '176', '4.62'),
('459', '180', '5.18'),
('459', '181', '5.18'),
('459', '185', '3.42'),
('459', '186', '3.42'),
('459', '766', '6.23'),
('459', '767', '6.23'),
('459', '768', '6.23'),
('459', '769', '6.23'),
('459', '851', '3.44'),
('459', '852', '3.44'),
('459', '853', '3.44'),
('459', '854', '3.44'),
('459', '1021', '4.65'),
('459', '1022', '4.65'),
('459', '1023', '4.65'),
('459', '1024', '4.65'),
('459', '1807', '3.18'),
('459', '1808', '3.18'),
('459', '1845', '1.84'),
('459', '1846', '1.84'),
('459', '1959', '3.09'),
('459', '1960', '3.09'),
('460', '176', '4.72'),
('460', '177', '4.72'),
('460', '181', '4.77'),
('460', '182', '4.77'),
('460', '186', '3.2'),
('460', '187', '3.2'),
('460', '769', '6.64'),
('460', '770', '6.64'),
('460', '771', '6.64'),
('460', '772', '6.64'),
('460', '854', '3.69'),
('460', '855', '3.69'),
('460', '856', '3.69'),
('460', '857', '3.69'),
('460', '1024', '4.58'),
('460', '1025', '4.58'),
('460', '1026', '4.58'),
('460', '1027', '4.58'),
('460', '1704', '0.1'),
('460', '1808', '2.9'),
('460', '1809', '2.9'),
('460', '1846', '1.56'),
('460', '1847', '1.56'),
('460', '1960', '3.02'),
('460', '1961', '3.02'),
('461', '178', '4.8'),
('461', '183', '4.99'),
('461', '188', '3.34'),
('461', '213', '4.8'),
('461', '215', '4.99'),
('461', '217', '3.34'),
('461', '772', '6.58'),
('461', '773', '6.58'),
('461', '774', '6.58'),
('461', '775', '6.58'),
('461', '857', '3.53'),
('461', '858', '3.53'),
('461', '859', '3.53'),
('461', '860', '3.53'),
('461', '1027', '4.46'),
('461', '1028', '4.46'),
('461', '1029', '4.46'),
('461', '1030', '4.46'),
('461', '1810', '3.19'),
('461', '1811', '3.19'),
('461', '1848', '1.59'),
('461', '1849', '1.59'),
('461', '1962', '2.91'),
('461', '1963', '2.91'),
('462', '5', '0.74'),
('462', '25', '0.74'),
('462', '26', '0.74'),
('462', '94', '0.74'),
('462', '112', '0.74'),
('462', '133', '0.74'),
('462', '152', '0.74'),
('462', '174', '0.74'),
('462', '175', '0.74'),
('462', '176', '0.74'),
('462', '177', '0.74'),
('462', '178', '0.74'),
('462', '213', '3.71'),
('462', '214', '3.71'),
('462', '215', '4.66'),
('462', '216', '4.66'),
('462', '217', '3.34'),
('462', '218', '3.34'),
('462', '775', '6.82'),
('462', '776', '6.82'),
('462', '777', '6.82'),
('462', '778', '6.82'),
('462', '860', '3.83'),
('462', '861', '3.83'),
('462', '862', '3.83'),
('462', '863', '3.83'),
('462', '1030', '4.55'),
('462', '1031', '4.55'),
('462', '1032', '4.55'),
('462', '1033', '4.55'),
('462', '1811', '2.93'),
('462', '1812', '2.93'),
('462', '1849', '1.58'),
('462', '1850', '1.58'),
('462', '1963', '2.61'),
('462', '1964', '2.61'),
('463', '287', '3.64'),
('463', '333', '3.64'),
('463', '383', '4.09'),
('463', '384', '4.09'),
('463', '409', '5.22'),
('463', '410', '5.22'),
('463', '778', '7.04'),
('463', '779', '7.04'),
('463', '780', '7.04'),
('463', '781', '7.04'),
('463', '863', '3.31'),
('463', '864', '3.31'),
('463', '865', '3.31'),
('463', '866', '3.31'),
('463', '1033', '4.67'),
('463', '1034', '4.67'),
('463', '1035', '4.67'),
('463', '1036', '4.67'),
('463', '1813', '2.86'),
('463', '1814', '2.86'),
('463', '1851', '1.71'),
('463', '1852', '1.71'),
('463', '1965', '2.44'),
('463', '1966', '2.44'),
('464', '333', '3.51'),
('464', '334', '3.51'),
('464', '384', '4'),
('464', '385', '4'),
('464', '410', '4.49'),
('464', '411', '4.49'),
('464', '781', '7.3'),
('464', '782', '7.3'),
('464', '783', '7.3'),
('464', '784', '7.3'),
('464', '866', '3.34'),
('464', '867', '3.34'),
('464', '868', '3.34'),
('464', '869', '3.34'),
('464', '1036', '4.68'),
('464', '1037', '4.68'),
('464', '1038', '4.68'),
('464', '1039', '4.68'),
('464', '1799', '0.4'),
('464', '1800', '0.4'),
('464', '1801', '0.4'),
('464', '1802', '0.4'),
('464', '1803', '0.4'),
('464', '1804', '0.4'),
('464', '1805', '0.4'),
('464', '1806', '0.4'),
('464', '1807', '0.4'),
('464', '1808', '0.4'),
('464', '1809', '0.4'),
('464', '1810', '0.4'),
('464', '1811', '0.4'),
('464', '1812', '0.4'),
('464', '1813', '0.4'),
('464', '1814', '2.29'),
('464', '1815', '2.29'),
('464', '1852', '1.98'),
('464', '1853', '1.98'),
('464', '1966', '2.58'),
('464', '1967', '2.58'),
('465', '335', '3.49'),
('465', '336', '3.49'),
('465', '386', '3.93'),
('465', '387', '3.93'),
('465', '412', '5.09'),
('465', '413', '5.09'),
('465', '784', '7.01'),
('465', '785', '7.01'),
('465', '786', '7.01'),
('465', '787', '7.01'),
('465', '869', '3.03'),
('465', '870', '3.03'),
('465', '871', '3.03'),
('465', '872', '3.03'),
('465', '1039', '4.84'),
('465', '1040', '4.84'),
('465', '1041', '4.84'),
('465', '1042', '4.84'),
('465', '1816', '3.15'),
('465', '1817', '3.15'),
('465', '1854', '1.99'),
('465', '1855', '1.99'),
('465', '1968', '2.64'),
('465', '1969', '2.64'),
('204', '41', '16.5'),
('204', '45', '29.4'),
('204', '66', '24.6'),
('204', '37', '29.4'),
('205', '40', '4.9'),
('205', '41', '7.5'),
('205', '45', '11.8'),
('205', '44', '12.7'),
('205', '42', '11.3'),
('205', '39', '9.6'),
('205', '66', '10.5'),
('205', '37', '7'),
('205', '38', '11.8'),
('205', '43', '7.1'),
('205', '36', '5.7'),
('181', '63', '18'),
('181', '61', '18'),
('181', '65', '10'),
('181', '64', '42'),
('181', '62', '12'),
('201', '39', '26.8'),
('201', '37', '15.7'),
('201', '38', '27.6'),
('201', '36', '29.9'),
('202', '40', '17.3'),
('202', '41', '24.8'),
('202', '42', '36.1'),
('202', '39', '21.8'),
('203', '40', '15'),
('203', '44', '25.5'),
('203', '39', '25'),
('203', '43', '34.5'),
('221', '54', '11.4'),
('221', '56', '9.7'),
('221', '52', '10.6'),
('221', '49', '11.8'),
('221', '50', '10.6'),
('221', '51', '11.2'),
('221', '55', '12.4'),
('221', '57', '12.5'),
('221', '53', '9.8'),
('222', '40', '20.7'),
('222', '41', '24.5'),
('222', '45', '20.8'),
('222', '43', '34'),
('243', '18', '3.5'),
('243', '16', '3'),
('243', '15', '2.7'),
('243', '19', '3.7'),
('243', '27', '2'),
('243', '17', '3.3'),
('243', '6', '3.3'),
('243', '11', '3.6'),
('243', '7', '3.8'),
('243', '8', '2.7'),
('243', '9', '2.9'),
('243', '35', '2.1'),
('243', '34', '1.5'),
('243', '32', '2.1'),
('243', '33', '2'),
('243', '31', '2'),
('243', '20', '3.4'),
('243', '26', '1.9'),
('243', '40', '15.7'),
('243', '10', '3.4'),
('243', '42', '5.4'),
('243', '13', '2.9'),
('243', '37', '4.6'),
('243', '38', '4.1'),
('243', '12', '3.3'),
('243', '5', '3.5'),
('243', '14', '3.5'),
('242', '11', '3.9'),
('242', '7', '3.3'),
('242', '8', '3'),
('242', '9', '3.1'),
('242', '35', '1.5'),
('242', '34', '1.7'),
('242', '32', '1.5'),
('242', '33', '1.5'),
('242', '31', '1.6'),
('242', '20', '3.3'),
('242', '26', '2.6'),
('242', '44', '5.8'),
('242', '40', '12.8'),
('242', '10', '3.8'),
('242', '18', '2.8'),
('242', '16', '3.4'),
('242', '15', '3.2'),
('242', '19', '3.3'),
('242', '27', '2.8'),
('242', '17', '3.2'),
('242', '6', '3.6'),
('242', '13', '2.9'),
('242', '37', '6'),
('242', '12', '3'),
('242', '5', '2.9'),
('242', '14', '3.7'),
('242', '67', '6.3'),
('241', '18', '3.6'),
('241', '16', '2.8'),
('241', '15', '3.4'),
('241', '19', '3.7'),
('241', '27', '4.3'),
('241', '17', '2.4'),
('241', '6', '3.7'),
('241', '11', '4'),
('241', '7', '1.4'),
('241', '8', '3.5'),
('241', '9', '5'),
('241', '35', '1.9'),
('241', '34', '2.1'),
('241', '32', '2.5'),
('241', '33', '1.9'),
('241', '31', '1.8'),
('241', '20', '3.3'),
('241', '26', '6.3'),
('241', '45', '5.8'),
('241', '10', '4'),
('241', '13', '4.1'),
('241', '37', '7.4'),
('241', '12', '4.4'),
('241', '5', '2.5'),
('241', '43', '4.4'),
('241', '14', '2.3'),
('241', '67', '7.4'),
('307', '39', '12.7'),
('307', '40', '7.7'),
('307', '42', '11.3'),
('307', '90', '13.4'),
('307', '88', '10.9'),
('307', '36', '10.5'),
('307', '91', '13.2'),
('307', '89', '20.4'),
('306', '39', '20.3'),
('306', '42', '20.9'),
('306', '90', '21.9'),
('306', '88', '23.2'),
('306', '36', '13.7'),
('308', '93', '13'),
('308', '40', '13.3'),
('308', '90', '14.9'),
('308', '88', '10.5'),
('308', '36', '12.6'),
('308', '91', '13.7'),
('308', '89', '21.9'),
('309', '92', '20.8'),
('309', '41', '23.1'),
('309', '93', '9.5'),
('309', '45', '9.3'),
('309', '37', '7.7'),
('309', '88', '10.5'),
('309', '43', '19.1'),
('310', '92', '7.4'),
('310', '39', '11.3'),
('310', '93', '7.4'),
('310', '40', '12.9'),
('310', '75', '3.9'),
('310', '42', '9.3'),
('310', '90', '7.9'),
('310', '88', '12.1'),
('310', '43', '4.3'),
('310', '36', '10.2'),
('310', '91', '13.2'),
('361', '18', '7.8'),
('361', '51', '16.7'),
('361', '20', '17.5'),
('361', '26', '8.6'),
('361', '40', '16.4'),
('361', '5', '15'),
('361', '89', '18.1'),
('261', '84', '9.7'),
('261', '15', '9.7'),
('261', '30', '8.5'),
('261', '69', '9.9'),
('261', '39', '11.4'),
('261', '81', '8.7'),
('261', '9', '9'),
('261', '79', '9.2'),
('261', '73', '11.4'),
('261', '85', '12.6'),
('362', '18', '12.4'),
('362', '50', '13.5'),
('362', '20', '13.4'),
('362', '26', '10.3'),
('362', '40', '13.3'),
('362', '5', '14.1'),
('362', '36', '11.7'),
('362', '67', '11.5'),
('363', '17', '20.4'),
('363', '56', '20.5'),
('363', '41', '21.4'),
('363', '99', '13.3'),
('363', '5', '12.5'),
('363', '14', '11.9'),
('281', '18', '24.1'),
('281', '20', '17.2'),
('281', '71', '21.2'),
('281', '78', '18.7'),
('281', '14', '18.7'),
('282', '68', '24.3'),
('282', '72', '19.4'),
('282', '20', '18.4'),
('282', '86', '17'),
('282', '14', '20.9'),
('321', '15', '9.6'),
('321', '6', '9.3'),
('321', '39', '16.5'),
('321', '99', '11.7'),
('321', '42', '18.2'),
('321', '88', '16.5'),
('321', '36', '18.3'),
('381', '16', '8.2'),
('381', '40', '14.5'),
('381', '56', '7.7'),
('381', '7', '8.1'),
('381', '45', '7.7'),
('381', '44', '7.3'),
('381', '5', '14.9'),
('381', '59', '8.8'),
('381', '43', '14.3'),
('381', '36', '8.5'),
('385', '16', '12.7'),
('385', '17', '13.2'),
('385', '7', '22.4'),
('385', '45', '17.6'),
('385', '43', '23.9'),
('385', '36', '10.2'),
('384', '40', '28.8'),
('384', '5', '24.1'),
('384', '36', '10.6'),
('384', '58', '13.6'),
('384', '60', '22.9'),
('383', '40', '35.5'),
('383', '5', '11.5'),
('383', '59', '11'),
('383', '53', '15.7'),
('383', '60', '26.3'),
('382', '16', '12.8'),
('382', '6', '18.7'),
('382', '59', '12.5'),
('382', '36', '19.8'),
('382', '58', '17.4'),
('382', '53', '18.8');
DELETE FROM `instance_encounters`;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '81021';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '81022';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-81021';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-81022';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81021, -109881, 0, 'Stampede -> Remove Ravage Marker');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81022, -109881, 0, 'Stampede -> Remove Ravage Marker');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81021, 109881, 0, 'Stampede -> Add Ravage Marker');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81022, 109881, 0, 'Stampede -> Add Ravage Marker');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (19750, -54149, 'Flash of Light -> Remove Infusion of Light');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (82326, -54149, 'Divine Light -> Remove Infusion of Light');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (82327, -54149, 'Holy Radiance -> Remove Infusion of Light');
UPDATE `npc_trainer` SET `spell`=93321 WHERE `entry`=200003 AND `spell`=79682;
UPDATE `npc_trainer` SET `spell`=93321 WHERE `entry`=48618 AND `spell`=79682;
DROP TABLE `content_emulation`;
UPDATE `creature_template` SET `unit_flags`=33554434 WHERE `entry`=46506 LIMIT 1;
UPDATE `creature_template` SET `exp`=3 WHERE `entry`=46506 LIMIT 1;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=44214;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=45322;
-- Author Locknes
-- Naxxramas update database part 
-- Creature texts
-- Anub'Rekhan
DELETE FROM `creature_text` WHERE `entry` = 15956;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15956, 0, 0, 'Just a little taste...', 14, 0, 100, 0, 0, 8785, 'anubrekhan SAY_AGGRO1'),
(15956, 0, 1, 'There is no way out.', 14, 0, 100, 0, 0, 8786, 'anubrekhan SAY_AGGRO2'),
(15956, 0, 2, 'Yes, run', 14, 0, 100, 0, 0, 8787, 'anubrekhan SAY_AGGRO3'),
(15956, 1, 0, 'Ahh... welcome to my parlor.', 14, 0, 100, 0, 0, 8788, 'anubrekhan SAY_GREET1'),
(15956, 1, 1, 'I hear little hearts beating. Yes... beating faster now... soon the beating will stop.', 14, 0, 100, 0, 0, 8790, 'anubrekhan SAY_GREET2'),
(15956, 1, 2, 'Where to go? What to do? So many choices that all end in pain, end in death.', 14, 0, 100, 0, 0, 8791, 'anubrekhan SAY_GREET3'),
(15956, 1, 3, 'Which one shall I eat first? So difficult to choose. They all smell so delicious...', 14, 0, 100, 0, 0, 8792, 'anubrekhan SAY_GREET4'),
(15956, 1, 4, 'Closer now. Tasty morsels. I\'ve been too long without food, without blood to drink.', 14, 0, 100, 0, 0, 8793, 'anubrekhan SAY_GREET5'),
(15956, 2, 0, 'Shhh... it will all be over soon.', 14, 0, 100, 0, 0, 8789, 'anubrekhan SAY_SLAY'),
(15956, 3, 0, 'Anub\'Rekhan begins to unleash an insect swarm', 41, 0, 0, 0, 0, 0, 'anubrekhan EMOTE_LOCUST_SWARM'),
(15956, 4, 0, ' A Crypt Guard joins the fight', 41, 0, 0, 0, 0, 0, 'anubrekhan EMOTE_CRYPT_GUARD'),
(15956, 5, 0, 'Corpse Scarabs appears from a Crypt Guard\'s corpse', 41, 0, 0, 0, 0, 0, 'anubrekhan EMOTE_CORPSE_SCARAB');
-- Grand Widow Faerlina
DELETE FROM `creature_text` WHERE `entry` = 15953;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15953, 0, 0, 'Your old lives, your mortal desires mean nothing... you are acolytes of the master now, and you will serve the cause without question', 14, 0, 100, 0, 0, 8799, 'faerlina SAY_GREET'),
(15953, 1, 1, 'You cannot hide from me', 14, 0, 100, 0, 0, 8795, 'faerlina SAY_AGGRO1'),
(15953, 1, 2, 'Kneel before me, worm', 14, 0, 100, 0, 0, 8796, 'faerlina SAY_AGGRO2'),
(15953, 1, 3, 'Run while you still can', 14, 0, 100, 0, 0, 8797, 'faerlina SAY_AGGRO3'),
(15953, 1, 4, 'Slay them in the master\'s name', 14, 0, 100, 0, 0, 8794, 'faerlina SAY_AGGRO4'),
(15953, 2, 0, 'You have failed', 14, 0, 100, 0, 0, 8800, 'faerlina SAY_SLAY1'),
(15953, 2, 1, 'Pathetic wretch', 14, 0, 100, 0, 0, 8801, 'faerlina SAY_SLAY2'),
(15953, 3, 0, 'The master will avenge me', 14, 0, 100, 0, 0, 8798, 'faerlina SAY_DEATH'),
(15953, 4, 0, 'Slay them in the master\'s name', 14, 0, 100, 0, 0, 8794, 'faerlina SAY_ENRAGE');
-- Four Horsemen
-- Thane Korth'azz
DELETE FROM `creature_text` WHERE `entry` = 16064;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(16064, 0, 0, 'Come out and fight, ye wee ninny', 14, 0, 100, 0, 0, 8899, 'korthazz SAY_KORT_AGGRO'),
(16064, 1, 0, 'To arms, ye roustabouts', 14, 0, 100, 0, 0, 8903, 'korthazz SAY_KORT_TAUNT1'),
(16064, 2, 0, 'I like my meat extra crispy', 14, 0, 100, 0, 0, 8902, 'korthazz SAY_KORT_SPECIAl'),
(16064, 3, 0, 'Next time, bring more friends', 14, 0, 100, 0, 0, 8901, 'korthazz SAY_KORT_SLAY'),
(16064, 4, 0, 'What a bloody waste this is', 14, 0, 100, 0, 0, 8900, 'korthazz SAY_KORT_DEATH'),
(16064, 5, 0, 'I heard about enough of yer sniveling. Shut yer fly trap \'afore I shut it for ye', 14, 0, 0, 0, 0, 8904, 'Korthazz SAY_HORSEMEN_6'),
(16064, 6, 0, 'I\'m gonna enjoy killin\' these slack-jawed daffodils', 14, 0, 100, 0, 0, 8905, 'korthazz SAY_KORT_TAUNT3');
-- Lady Blaumeux
DELETE FROM `creature_text` WHERE `entry` = 16065;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(16065, 0, 0, 'Defend youself', 14, 0, 100, 0, 0, 8892, 'blaumeux SAY_BLAU_AGGRO'),
(16065, 1, 0, 'The first kill goes to me Anyone care to wager?', 14, 0, 100, 0, 0, 8898, 'blaumeux SAY_BLAU_TAUNT3'),
(16065, 2, 0, 'Your life is mine', 14, 0, 100, 0, 0, 8895, 'blaumeux SAY_BLAU_SPECIAL'),
(16065, 3, 0, 'Who\'s next?', 14, 0, 100, 0, 0, 8894, 'blaumeux SAY_BLAU_SLAY'),
(16065, 4, 0, 'Tou... che', 14, 0, 100, 0, 0, 8893, 'blaumeux SAY_BLAU_DEATH'),
(16065, 5, 0, 'Come, Zeliek, do not drive them out. Not before we\'ve had our fun.', 14, 0, 0, 0, 0, 8896, 'Blaumeux SAY_HORSEMEN_2'),
(16065, 6, 0, 'I do hope they stay alive long enough for me to... introduce myself.', 14, 0, 0, 0, 0, 8897, 'Blaumeux SAY_HORSEMEN_4');
-- Baron Rivendare
DELETE FROM `creature_text` WHERE `entry` = 30549;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(30549, 0, 0, 'You seek death?', 14, 0, 100, 0, 0, 14571, 'rivendare SAY_RIVE_AGGRO1'),
(30549, 0, 1, 'None shall pass', 14, 0, 100, 0, 0, 14572, 'rivendare SAY_RIVE_AGGRO2'),
(30549, 0, 2, 'Be still', 14, 0, 100, 0, 0, 14573, 'rivendare SAY_RIVE_AGGRO3'),
(30549, 1, 2, 'Life is meaningless. It is in death that we are truly tested.', 14, 0, 100, 0, 0, 14579, 'rivendare SAY_RIVE_TAUNT3'),
(30549, 2, 0, 'Bow to the might of the scourge', 14, 0, 100, 0, 0, 14576, 'rivendare SAY_RIVE_SPECIAL'),
(30549, 3, 0, 'You will find no peace in death.', 14, 0, 100, 0, 0, 14574, 'rivendare SAY_RIVE_SLAY1'),
(30549, 3, 1, 'The master\'s will is done.', 14, 0, 100, 0, 0, 14575, 'rivendare SAY_RIVE_SLAY2'),
(30549, 4, 0, 'Death... will not stop me...', 14, 0, 100, 0, 0, 14580, 'rivendare SAY_RIVE_DEATH'),
(30549, 5, 0, 'Enough prattling. Let them come We shall grind their bones to dust.', 14, 0, 0, 0, 0, 14577, 'Rivendare SAY_HORSEMEN_3'),
(30549, 6, 0, 'Conserve your anger You will all have outlets for your frustration soon enough.', 14, 0, 0, 0, 0, 14578, 'Rivendare SAY_HORSEMEN_7');
-- Sir Zeliek
DELETE FROM `creature_text` WHERE `entry` = 16063;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(16063, 0, 0, 'Do not continue', 14, 0, 100, 0, 0, 8919, 'zeliek SAY_ZELI_TAUNT3'),
(16063, 1, 0, 'Flee, before it\'s too late', 14, 0, 100, 0, 0, 8913, 'zeliek SAY_ZELI_AGGRO'),
(16063, 2, 0, 'I- I have no choice but to obey', 14, 0, 100, 0, 0, 8916, 'zeliek SAY_ZELI_SPECIAL'),
(16063, 3, 0, 'Forgive me', 14, 0, 100, 0, 0, 8915, 'zeliek SAY_ZELI_SLAY'),
(16063, 4, 0, 'It is... as it should be.', 14, 0, 100, 0, 0, 8914, 'zeliek SAY_ZELI_DEATH'),
(16063, 5, 0, 'Invaders, cease this foolish venture at once', 14, 0, 0, 0, 0, 8917, 'Zeliek SAY_HORSEMEN_1'),
(16063, 6, 0, 'Perhaps they will come to their senses, and run away as fast as they can', 14, 0, 0, 0, 0, 8918, 'Zeliek SAY_HORSEMEN_5');
-- Gluth
DELETE FROM `creature_text` WHERE `entry` = 15932;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15932, 0, 0, 'Gluth becomes enraged', 41, 0, 0, 0, 0, 0, 'Gluth EMOTE_ENRAGE'),
(15932, 1, 0, 'Gluth decimates all nearby flesh', 41, 0, 0, 0, 0, 0, 'Gluth EMOTE_DECIMATE'),
(15932, 2, 0, '%s spots a nearby zombie to devour', 41, 0, 0, 0, 0, 0, 'Gluth EMOTE_NEARBY');
-- Gothik the Harvester
DELETE FROM `creature_text` WHERE `entry` = 16060;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(16060, 0, 0, 'Foolishly you have sought your own demise. Brazenly you have disregarded powers beyond your understanding. You have fought hard to invade the realm of the harvester. Now there is only one way out - to walk the lonely path of the damned.', 14, 0, 100, 0, 0, 8807, 'gothik SAY_SPEECH'),
(16060, 1, 0, 'Death is the only escape.', 14, 0, 100, 0, 0, 8806, 'gothik SAY_KILL'),
(16060, 2, 0, 'I... am... undone', 14, 0, 100, 0, 0, 8805, 'gothik SAY_DEATH'),
(16060, 3, 0, 'I have waited long enough', 14, 0, 100, 0, 0, 8808, 'gothik SAY_TELEPORT');
-- Grobbulus
DELETE FROM `creature_text` WHERE `entry` = 15931;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15931, 0, 0, 'Grobbulus sprays slime across the room', 41, 0, 0, 0, 0, 0, 'Grobbulus EMOTE_SPRAY');
-- Heigan the Unclean
DELETE FROM `creature_text` WHERE `entry` = 15936;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15936, 0, 1, 'I see you...', 14, 0, 0, 0, 0, 8826, 'Heigan SAY_AGGRO'),
(15936, 0, 0, 'You are mine now.', 14, 0, 0, 0, 0, 8825, 'Heigan SAY_AGGRO'),
(15936, 0, 2, 'You... are next.', 14, 0, 0, 0, 8827, 0, 'Heigan SAY_AGGRO'),
(15936, 1, 0, 'Close your eyes. Sleep.', 14, 0, 0, 0, 0, 8829, 'Heigan SAY_KILL'),
(15936, 2, 0, 'The end is upon you.', 14, 0, 0, 0, 0, 8833, 'Heigan SAY_PHASE'),
(15936, 3, 0, 'Heigan the Unclean teleports and begins to channel  a spell', 41, 0, 0, 0, 0, 0, 'Heigan EMOTE_TELEPORT'),
(15936, 4, 0, 'Heigan the Unclean rushes to attack once more', 41, 0, 0, 0, 0, 0, 'Heigan EMOTE_TELEPORT'),
(15936, 5, 0, '%s takes his last breath.', 16, 0, 0, 0, 0, 0, 'Heigan SAY_DEATH');
-- Kel'Thuzad
DELETE FROM `creature_text` WHERE `entry` = 15990;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15990, 0, 0, 'No The armies of the Lich King will hunt you down. You will not escape your fate...', 14, 0, 100, 0, 0, 14484, 'kelthuzad SAY_CAT_DIED'),
(15990, 1, 0, 'Who dares violate the sanctity of my domain? Be warned, all who trespass here are doomed.', 14, 0, 100, 0, 0, 14463, 'kelthuzad SAY_TAUNT1'),
(15990, 2, 0, 'Fools', 14, 0, 100, 0, 0, 14464, 'kelthuzad SAY_TAUNT2'),
(15990, 3, 0, 'I grow tired of these games. Proceed, and I will banish your souls to oblivion', 14, 0, 100, 0, 0, 14465, 'kelthuzad SAY_TAUNT3'),
(15990, 4, 0, 'You have no idea what horrors lie ahead. You have seen nothing', 14, 0, 100, 0, 0, 14466, 'kelthuzad SAY_TAUNT4'),
(15990, 5, 0, 'Your forces are nearly marshaled to strike back against your enemies, my liege.', 14, 0, 100, 0, 0, 14467, 'kelthuzad SAY_SAPP_DIALOG1'),
(15990, 6, 0, 'Yes, master. The time of their ultimate demise draws close.... What is this?', 14, 0, 100, 0, 0, 14468, 'kelthuzad SAY_SAPP_DIALOG3'),
(15990, 7, 0, 'As you command, master', 14, 0, 100, 0, 0, 14469, 'kelthuzad SAY_SAPP_DIALOG5'),
(15990, 8, 0, 'Pray for mercy', 14, 0, 100, 0, 0, 14475, 'kelthuzad SAY_AGGRO1'),
(15990, 8, 1, 'Scream your dying breath', 14, 0, 100, 0, 0, 14476, 'kelthuzad SAY_AGGRO2'),
(15990, 8, 2, 'The end is upon you', 14, 0, 100, 0, 0, 14477, 'kelthuzad SAY_AGGRO3'),
(15990, 9, 0, 'The dark void awaits you', 14, 0, 100, 0, 0, 14478, 'kelthuzad SAY_SLAY1'),
(15990, 9, 1, '%s cackles maniacally.', 16, 0, 100, 0, 0, 14479, 'kelthuzad SAY_SLAY2'),
(15990, 10, 0, 'Agghhhh Your victory is a hollow one, for I shall return with powers beyond your imagining', 14, 0, 100, 0, 0, 14480, 'kelthuzad SAY_DEATH'),
(15990, 11, 0, 'Your soul is bound to me, now', 14, 0, 100, 0, 0, 14472, 'kelthuzad SAY_CHAIN1'),
(15990, 11, 1, 'There will be no escape', 14, 0, 100, 0, 0, 14473, 'kelthuzad SAY_CHAIN2'),
(15990, 12, 0, 'I will freeze the blood in your veins', 14, 0, 100, 0, 0, 14474, 'kelthuzad SAY_FROST_BLAST'),
(15990, 13, 0, 'Master, I require aid', 14, 0, 100, 0, 0, 14470, 'kelthuzad SAY_REQUEST_AID'),
(15990, 14, 0, 'Minions, servants, soldiers of the cold dark', 14, 0, 100, 0, 0, 14471, 'kelthuzad SAY_SUMMON_MINIONS'),
(15990, 15, 0, 'Your petty magics are no challenge to the might of the Scourge ', 14, 0, 100, 0, 0, 14481, 'kelthuzad SAY_SPECIAL1_MANA_DET'),
(15990, 15, 1, 'Enough ', 14, 0, 100, 0, 0, 14483, 'kelthuzad SAY_SPECIAL3_MANA_DET'),
(15990, 15, 2, 'Fools, you have spread your powers too thin. Be free, my minions', 14, 0, 100, 0, 0, 14482, 'kelthuzad SAY_SPECIAL2_DISPELL'),
(15990, 16, 0, 'Kel\'Thuzad strikes.', 41, 0, 0, 0, 0, 0, 'Kelthuzad EMOTE_ATTACK'),
(15990, 17, 0, 'A Guardian of Icecrown enters the fight.', 41, 0, 0, 0, 0, 0, 'Kelthuzad EMOTE_GUARDIAN');
-- Loatheb
DELETE FROM `creature_text` WHERE `entry` = 16011;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(16011, 0, 0, 'An aura of necrotic energy blocks all healing', 41, 0, 100, 0, 0, 0, 'Loatheb_AURA_APPLIED'),
(16011, 1, 0, 'The aura fades away, allowing for healing once more', 41, 0, 100, 0, 0, 0, 'Loatheb_AURA_REMOVED'),
(16011, 2, 0, 'The aura\'s power begins to wane', 41, 0, 100, 0, 0, 0, 'Loatheb_AURA_FADING');
-- Maexxna
DELETE FROM `creature_text` WHERE `entry` = 15952;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15952, 0, 0, 'Maexxna spins her web into a coccon', 41, 0, 0, 0, 0, 0, 'Maexxna EMOTE_WRAP'),
(15952, 1, 0, 'Spiderlings appear on the web', 41, 0, 0, 0, 0, 0, 'Maexxna EMOTE_SPIDERLING');
-- Noth
DELETE FROM `creature_text` WHERE `entry` = 15954;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15954, 0, 0, 'Glory to the master', 14, 0, 100, 0, 0, 8845, 'noth SAY_AGGRO1'),
(15954, 0, 1, 'Your life is forfeit', 14, 0, 100, 0, 0, 8846, 'noth SAY_AGGRO2'),
(15954, 0, 2, 'Die, trespasser', 14, 0, 100, 0, 0, 8847, 'noth SAY_AGGRO3'),
(15954, 1, 0, 'Rise, my soldiers', 14, 0, 100, 0, 0, 8851, 'noth SAY_SUMMON'),
(15954, 2, 0, 'My task is done', 14, 0, 100, 0, 0, 8849, 'noth SAY_SLAY1'),
(15954, 2, 1, 'Breathe no more', 14, 0, 100, 0, 0, 8850, 'noth SAY_SLAY2'),
(15954, 3, 0, 'I will serve the master... in... death', 14, 0, 100, 0, 0, 8848, 'noth SAY_DEATH'),
(15954, 4, 0, 'Noth the Plaguebringer summons forth Skeletal Warrios', 41, 0, 0, 0, 0, 0, 'noth EMOTE_SUMMON'),
(15954, 5, 0, 'Noth the Plaguebringer teleports to the balcony above', 41, 0, 0, 0, 0, 0, 'noth EMOTE_BALCONY'),
(15954, 6, 0, 'Noth the Plaguebringer raises more skeletons', 41, 0, 0, 0, 0, 0, 'noth EMOTE_SKELETON'),
(15954, 7, 0, 'Noth the Plaguebringer teleports back into the battle', 41, 0, 0, 0, 0, 0, 'noth EMOTE_TELEPORT'),
(15954, 8, 0, 'Noth the Plaguebringer blinks away', 41, 0, 0, 0, 0, 0, 'noth EMOTE_BLINK');
-- Patchwerk
DELETE FROM `creature_text` WHERE `entry` = 16028;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(16028, 0, 1, 'Kel\'Thuzad make Patchwerk his avatar of war', 14, 0, 0, 0, 0, 8910, 'Patchwerk SAY_AGGRO'),
(16028, 0, 0, 'Patchwerk want to play.', 14, 0, 0, 0, 0, 8909, 'Patchwerk SAY_AGGRO'),
(16028, 1, 0, 'No more play?', 14, 0, 0, 0, 0, 8912, 'Patchwerk SAY_KILL'),
(16028, 2, 0, 'What happened to... Patch...', 14, 0, 0, 0, 0, 8911, 'Patchwerk SAY_DEATH'),
(16028, 3, 0, '%s goes into a berserker rage', 16, 0, 0, 0, 0, 0, 'Patchwerk EMOTE_BERSERK'),
(16028, 4, 0, 'Patchwerk becomes enraged', 41, 0, 0, 0, 0, 0, 'Patchwerk EMOTE_ENRAGE');
-- Instructor Razuvious
DELETE FROM `creature_text` WHERE `entry` = 16061;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(16061, 0, 0, 'Do as I taught you', 14, 0, 0, 0, 0, 8855, 'Razuvious SAY_AGGRO'),
(16061, 0, 1, 'Show them no mercy', 14, 0, 0, 0, 0, 8856, 'Razuvious SAY_AGGRO'),
(16061, 0, 3, 'Sweep the leg Do you have a problem with that?', 14, 0, 0, 0, 0, 8861, 'Razuvious SAY_AGGRO'),
(16061, 0, 2, 'The time for practice is over', 14, 0, 0, 0, 0, 8859, 'Razuvious SAY_AGGRO'),
(16061, 1, 0, 'Hah hah, I\'m just getting warmed up', 14, 0, 0, 0, 0, 8852, 'Razuvious SAY_COMMND'),
(16061, 1, 2, 'Show me what you\'ve got', 14, 0, 0, 0, 0, 8854, 'Razuvious SAY_COMMND'),
(16061, 1, 1, 'Stand and fight', 14, 0, 0, 0, 0, 8853, 'Razuvious SAY_COMMND'),
(16061, 1, 4, 'You disappoint me, students', 14, 0, 0, 0, 0, 8858, 'Razuvious SAY_COMMND'),
(16061, 1, 3, 'You should\'ve stayed home', 14, 0, 0, 0, 0, 8861, 'Razuvious SAY_COMMND'),
(16061, 2, 0, 'An honorable... death...', 14, 0, 0, 0, 0, 8860, 'Razuvious SAY_DEATH');
-- Sapphiron
DELETE FROM `creature_text` WHERE `entry` = 15989;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15989, 0, 0, 'Sapphiron lifts off into the air', 41, 0, 0, 0, 0, 0, 'Sapphiron EMOTE_AIR'),
(15989, 1, 0, 'Sapphiron resmues his attacks', 41, 0, 0, 0, 0, 0, 'Sapphiron EMOTE_LAND'),
(15989, 2, 0, 'Sapphiron takes a deep breath.', 41, 0, 0, 0, 0, 0, 'Sapphiron EMOTE_BREATH'),
(15989, 3, 0, '%s enrages', 16, 0, 0, 0, 0, 0, 'Sapphiron EMOTE_ENRAGE');
-- Stalagg
DELETE FROM `creature_text` WHERE `entry` = 15929;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15929, 0, 0, 'Stalagg crush you', 14, 0, 0, 0, 0, 8864, 'Stalagg SAY_AGGRO'),
(15929, 1, 0, 'Stalagg kill', 14, 0, 0, 0, 0, 8866, 'Stalagg SAY_KILL'),
(15929, 2, 0, 'Master save me...', 14, 0, 0, 0, 0, 8865, 'Stalagg SAY_DEATH');
-- Feugen
DELETE FROM `creature_text` WHERE `entry` = 15930;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15930, 0, 0, 'Feed you to master', 14, 0, 0, 0, 0, 8802, 'Feugen SAY_AGGRO'),
(15930, 1, 0, 'Feugen make master happy', 14, 0, 0, 0, 0, 8804, 'Feugen SAY_KILL'),
(15930, 2, 0, 'No... more... Feugen...', 14, 0, 0, 0, 0, 8803, 'Feugen SAY_DEATH');
-- Thaddius
DELETE FROM `creature_text` WHERE `entry` = 15928;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(15928, 0, 0, 'You are too late... I... must... OBEY', 14, 0, 0, 0, 0, 8872, 'Thaddius SAY_GREET'),
(15928, 1, 1, 'BREAK YOU', 14, 0, 0, 0, 0, 8869, 'Thaddius SAY_AGGRO'),
(15928, 1, 0, 'EAT YOUR BONES', 14, 0, 0, 0, 0, 8868, 'Thaddius SAY_AGGRO'),
(15928, 1, 2, 'KILL', 14, 0, 0, 0, 0, 8867, 'Thaddius SAY_AGGRO'),
(15928, 2, 0, 'Thank... you...', 14, 0, 0, 0, 0, 8870, 'Thaddius SAY_DEATH'),
(15928, 3, 0, 'Now you feel pain', 14, 0, 0, 0, 0, 8871, 'Thaddius SAY_ELECT'),
(15928, 4, 0, 'You die now', 14, 0, 0, 0, 0, 8877, 'Thaddius SAY_KILL'),
(15928, 5, 0, 'The polarity has shifted', 41, 0, 0, 0, 0, 0, 'Thaddis EMOTE_SHIFT');
-- Lich king
DELETE FROM `creature_text` WHERE `entry` = 28765;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(28765, 1, 0, 'Soon we will eradicate the Alliance and Horde, then the rest of Azeroth will fall before the might of my army.', 14, 0, 0, 0, 0, 14768, 'The Lich King SAY_SAPP_DIALOG2_LICH'),
(28765, 2, 0, 'Very well... warriors of the frozen wastes, rise up I command you to fight, kill, and die for your master. Let none survive...', 14, 0, 0, 0, 0, 8824, 'The Lich King SAY_ANSWER'),
(28765, 3, 0, 'Invaders...here? Naxxramas must not fall', 14, 0, 0, 0, 0, 14769, 'The Lich King SAY_SAPP_DIALOG4_LICH');
-- Teleports template
DELETE FROM `gameobject_template` WHERE `entry` IN (181575,181576,181577,181578);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `AIName`, `ScriptName`, `WDBVerified`) VALUES
(181575, 10, 6787, 'Naxxramas Portal', '', '', '', 0, 32, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28444, 1, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(181578, 10, 6790, 'Naxxramas Portal', '', '', '', 0, 32, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28444, 1, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(181576, 10, 6788, 'Naxxramas Portal', '', '', '', 0, 32, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28444, 1, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(181577, 10, 6789, 'Naxxramas Portal', '', '', '', 0, 32, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28444, 1, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);
-- Orbs template
DELETE FROM `gameobject_template` WHERE `entry` IN (202277,202278);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `AIName`, `ScriptName`, `WDBVerified`) VALUES
(202278, 10, 7800, 'Orb of Naxxramas', '', '', '', 0, 32, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 72617, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(202277, 10, 7800, 'Orb of Naxxramas', '', '', '', 0, 32, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 72613, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);
-- Scriptnames
UPDATE `gameobject_template` SET `ScriptName`='go_naxxramas_portal' WHERE `entry` IN (181575,181576,181577,181578);
UPDATE `gameobject_template` SET `ScriptName`='go_orb_of_naxxramas' WHERE `entry` IN (202277,202278);
-- Disable movement for Eye Stalkers
UPDATE `creature_template` SET `unit_flags`=4 WHERE `entry`=16236;
-- Delete areatrigger teleport non blizz data
DELETE FROM `areatrigger_teleport` WHERE  `id`=4156;
-- Add areatrigger scripts
DELETE FROM `areatrigger_scripts` WHERE `entry` IN (4113,4115,4117,4119);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(4115, 'at_faerlina_intro'),
(4117, 'at_millitary_quarter'),
(4113, 'at_thaddius_intro'),
(4119, 'at_anubrekhan_intro');
-- Spawn Orb of Naxxramas
DELETE FROM `gameobject` WHERE `guid` IN (191946,191945);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(191946, 202277, 533, 3, 1, 3495.97, -5357.84, 144.964, 0.541051, 0, 0, 0.267238, 0.963631, 7200, 255, 1),
(191945, 202278, 533, 3, 1, 2997.68, -3437.8, 304.2, 1.15192, 0, 0, 0.544639, 0.838671, 7200, 255, 1);
-- Spawn teleports
DELETE FROM `gameobject` WHERE `guid` IN (30006,30007,30008,30009);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(30009, 181575, 533, 3, 1, 3465.18, -3940.4, 308.79, 2.44, 0, 0, 0.939099, 0.343646, 604800, 100, 1),
(30006, 181576, 533, 3, 1, 3539.02, -2936.82, 302.48, 3.14, 0, 0, 1, 0.000796274, 604800, 100, 1),
(30007, 181577, 533, 3, 1, 2909, -4025.02, 273.48, 3.14, 0, 0, 1, 0.000796274, 604800, 100, 1),
(30008, 181578, 533, 3, 1, 2493.02, -2921.78, 241.19, 3.14, 0, 0, 1, 0.000796274, 604800, 100, 1);
-- Add target for Naxxramas spells
DELETE FROM `spell_target_position` WHERE `id` IN (29273,29231,29216,29247,29248,29249,29237,29217,29224,29225,29227,29238,29255,29257,29258,29262,29267,29226,29239,29256,29268,30211,28025,28026,72613,28444,72617,54862,29240);
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(29273, 533, 3498.28, -5349.9, 144.968, 1.31324),
(29231, 533, 2684.8, -3502.52, 261.31, 0),
(29216, 533, 2631.37, -3529.68, 274.04, 0),
(29247, 533, 2648.83, -3467.3, 262.399, 5.46297),
(29248, 533, 2704.13, -3462.44, 262.403, 4.31236),
(29249, 533, 2722.42, -3514.74, 262.467, 3.09084),
(29237, 533, 2648.83, -3467.3, 262.399, 5.46297),
(29217, 533, 2642.34, -3485.28, 262.273, 6.17666),
(29224, 533, 2646.55, -3471.47, 262.413, 5.43839),
(29225, 533, 2651.09, -3464.07, 262.112, 5.45017),
(29227, 533, 2663.92, -3464.7, 262.574, 5.15958),
(29238, 533, 2684.95, -3457.55, 262.578, 4.62159),
(29255, 533, 2704.22, -3461.86, 262.546, 4.37027),
(29257, 533, 2724.82, -3466.21, 262.622, 3.85584),
(29258, 533, 2722.03, -3514.3, 262.354, 2.84269),
(29262, 533, 2726.13, -3534.64, 262.31, 2.60314),
(29267, 533, 2711.72, -3458.56, 262.384, 4.02864),
(29226, 533, 2722.29, -3514.68, 262.431, 2.87018),
(29239, 533, 2706.78, -3461.59, 262.517, 4.00358),
(29256, 533, 2669.42, -3463.75, 262.63, 5.07774),
(29268, 533, 2646.93, -3470.95, 262.427, 5.51363),
(30211, 533, 2793.86, -3707.38, 276.64, 2.32),
(28025, 533, 2692.65, -3321.06, 267.684, 4.70454),
(28026, 533, 2705.95, -3412.45, 267.688, 2.19126),
(72613, 533, 3004.58, -3392.53, 298, 5.796),
(28444, 533, 3005.46, -3433.96, 304.195, 3.593),
(72617, 533, 3497.45, -5354.67, 144.975, 1.321),
(54862, 533, 2704.22, -3461.86, 262.546, 4.37027),
(29240, 533, 2704.22, -3461.86, 262.546, 4.37027);
-- Spawn Tesla objects
DELETE FROM `gameobject` WHERE `guid` IN (30010,30011);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(30010, 181477, 533, 3, 1, 3527.94, -2952.26, 318.9, 3.14, 0, 0, 1, 0.000796274, 604800, 100, 1),
(30011, 181478, 533, 3, 1, 3487.32, -2911.38, 318.9, 3.14, 0, 0, 1, 0.000796274, 604800, 100, 1);
-- Spawn Tesla triggers
DELETE FROM `creature` WHERE `guid` IN (300000,300001);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(300000, 16218, 533, 3, 1, 0, 0, 3487.76, -2911.2, 319.406, 3.90954, 300, 0, 0, 17010, 0, 0, 0, 0, 0),
(300001, 16218, 533, 3, 1, 0, 0, 3527.81, -2952.38, 319.326, 3.90954, 300, 0, 0, 17010, 0, 0, 0, 0, 0);
-- Set fly for Tesla triggers
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=16218;
-- Add conditions for Stalagg's and Feugen's chain
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` IN (28111,28096);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13, 1, 28111, 0, 0, 31, 0, 3, 15930, 0, 0, 0, '', ''),
(13, 1, 28096, 0, 0, 31, 0, 3, 15929, 0, 0, 0, '', '');
-- Add spell difficulties
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (28783,28785,28796,28794,28798,28732,28371,28374,29317,28157,29998,28478,28479,29865,29204,29484,28741,28776,54123,29213,29212,41926,29107,28134,28135,28167);
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`) VALUES
-- Anub'Rekhan
(28783, 28783, 56090),
(28785, 28785, 54021),
-- Grand Widow Faerlina
(28796, 28796, 54098),
(28794, 28794, 54099),
(28798, 28798, 54100),
(28732, 28732, 54097),
-- Gluth
(28371, 28371, 54427),
(28374, 28374, 54426),
-- Gothik the Harvester
(29317, 29317, 56405),
-- Grobbulus
(28157, 28157, 54364),
-- Heigan the Unclean
(29998, 29998, 55011),
-- Kel'Thuzad
(28478, 28478, 55802),
(28479, 28479, 55807),
-- Loatheb
(29865, 29865, 55053),
(29204, 29204, 55052),
-- Maexxna
(29484, 29484, 54125),	
(28741, 28741, 54122),
(28776, 28776, 54121),
(54123, 54123, 54124),
-- Noth the Plaguebringer
(29213, 29213, 54835),
(29212, 29212, 54814),
-- Patchwerk
(41926, 41926, 59192),
-- Instructor Razuvious
(29107, 29107, 55543),
-- Stalagg
(28134, 28134, 54529),
-- Feugen
(28135, 28135, 54528),
-- Thaddius
(28167, 28167, 54531);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (86347, 11426, 'Reactive Barrier -> Cast Ice Barrier');
DELETE FROM spell_script_names WHERE scriptname = 'spell_mage_cone_of_cold';
REPLACE INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES
(38796, 2842, 100, 0, 0, 10),
(38517, 2842, 100, 0, 0, 10),
(36630, 2842, 100, 0, 0, 10),
(36524, 2842, 100, 0, 0, 10),
(35806, 2842, 100, 0, 0, 10),
(49870, 2842, 950, 0, 0, 10),
(4215, 2842, 950, 0, 0, 10),
(4582, 2842, 950, 0, 0, 10),
(50027, 2842, 950, 0, 0, 10),
(2122, 2842, 950, 0, 0, 10),
(50016, 2842, 950, 0, 0, 10),
(49949, 2842, 950, 0, 0, 10),
(50158, 2842, 950, 0, 0, 10),
(16685, 2842, 950, 0, 0, 10),
(4214, 2842, 950, 0, 0, 10),
(6707, 2842, 950, 0, 0, 10),
(49782, 2842, 950, 0, 0, 10),
(3327, 2842, 950, 0, 0, 10),
(47233, 2842, 950, 0, 0, 10),
(4584, 2842, 950, 0, 0, 10),
(50147, 2842, 950, 0, 0, 10),
(1234, 2842, 950, 0, 0, 10),
(5165, 2842, 950, 0, 0, 10),
(1411, 2842, 950, 0, 0, 10),
(3599, 2842, 950, 0, 0, 10),
(915, 2842, 950, 0, 0, 10),
(3170, 2842, 950, 0, 0, 10),
(42366, 2842, 950, 0, 0, 10),
(49939, 2842, 950, 0, 0, 10),
(917, 2842, 950, 0, 0, 10),
(49909, 2842, 950, 0, 0, 10),
(50498, 2842, 950, 0, 0, 10),
(2130, 2842, 950, 0, 0, 10),
(4583, 2842, 950, 0, 0, 10),
(50015, 2842, 950, 0, 0, 10),
(16686, 2842, 950, 0, 0, 10),
(3328, 2842, 950, 0, 0, 10),
(5166, 2842, 950, 0, 0, 10),
(918, 2842, 950, 0, 0, 10),
(5167, 2842, 950, 0, 0, 10),
(3155, 2842, 950, 0, 0, 10),
(13283, 2842, 950, 0, 0, 10),
(49745, 2842, 950, 0, 0, 10),
(48615, 2842, 950, 0, 0, 10),
(4163, 2842, 950, 0, 0, 10),
(45095, 2842, 950, 0, 0, 10),
(50127, 2842, 950, 0, 0, 10),
(916, 2842, 950, 0, 0, 10),
(45717, 2842, 950, 0, 0, 10),
(51998, 2842, 950, 0, 0, 10),
(35811, 2842, 950, 0, 0, 10),
(3594, 2842, 950, 0, 0, 10),
(16279, 2842, 950, 0, 0, 10),
(16684, 2842, 950, 0, 0, 10),
(38244, 2842, 950, 0, 0, 10),
(23566, 2842, 950, 0, 0, 10),
(15285, 2842, 950, 0, 0, 10);
DELETE FROM `spell_script_names` WHERE `spell_id` = '85222';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (85222, 'spell_pal_light_of_dawn');
DELETE FROM `spell_script_names` WHERE  `spell_id`=77829;
DELETE FROM `spell_script_names` WHERE  `spell_id`=77830;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (77829, 'spell_sha_ancestral_resolve');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (77830, 'spell_sha_ancestral_resolve');
DELETE FROM `spell_script_names` WHERE `spell_id` = '31228';
DELETE FROM `spell_script_names` WHERE `spell_id` = '31229';
DELETE FROM `spell_script_names` WHERE `spell_id` = '31230';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (31228, 'spell_rog_cheat_death');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (31229, 'spell_rog_cheat_death');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (31230, 'spell_rog_cheat_death');
REPLACE INTO spell_ranks VALUES
(35104, 35104, 1),
(35104, 35110, 2),
(53221, 53221, 1),
(53221, 53222, 2),
(53221, 53224, 3),
(53241, 53241, 1),
(53241, 53243, 2),
(34485, 34485, 1),
(34485, 34486, 2),
(34485, 34487, 3);
REPLACE INTO spell_proc_event VALUES
(53241, 0, 9, 0, 0, 0, 0x100, 0, 0, 100, 0),
(53243, 0, 9, 0, 0, 0, 0x100, 0, 0, 100, 0);
DELETE FROM spell_proc_event WHERE entry IN (53221, 53222, 53224);
REPLACE INTO spell_script_names VALUES
(-34485, "spell_hun_master_marksman"),
(82926, "spell_hun_fire"),
(-35104, "spell_hun_bombardement"),
(-53241, "spell_hun_marked_for_death");
DELETE FROM `spell_script_names` WHERE `spell_id` = '63560';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (63560, 'spell_dk_dark_transformation');
DELETE FROM `game_event_npc_vendor` WHERE `eventEntry` NOT IN (SELECT `eventEntry` FROM `game_event`);
DELETE FROM `npc_vendor` WHERE `entry` IN (54660, 54661, 54662, 44245, 58154, 44246, 46556, 46555, 58155, 54657, 54658, 54659, 12795, 12794, 12784, 12785);
﻿
UPDATE `command` SET `security`= 3 WHERE `security` IN (4, 5);
﻿-- Firelands Trash stuff --
-- Molten Lord
UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'npc_fl_molten_lord' WHERE `entry`= 53115;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 53115;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`= 99555;
-- Shannox
UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'npc_fl_shannox_trash' WHERE `entry` IN
(53206, 53128, 53095, 53127, 53141, 53134, 53096, 53094, 53732, 53167);
-- Shannox Controller
UPDATE `creature_template` SET `scriptname`= 'npc_fl_shannox_controller' WHERE `entry`= 53910;
DELETE FROM `creature_text` WHERE `entry` = 53910;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(53910, 0, 0, '|TInterface\\Icons\\inv_misc_horn_03.blp:20|tAs the creatures of the Firelands fall, heard the horn of a hunter in the distance.', 41, 0, 100, 0, 0, 6423, 'Shannox Controller'),
(53910, 1, 0, '|TInterface\\Icons\\inv_misc_horn_03.blp:20|tThe hunting horn sounded again, closer and penetrating.', 41, 0, 100, 0, 0, 6423, 'Shannox Controller');
-- Shannox                        rageface / riblimp
DELETE FROM `creature` WHERE `id` IN (53695, 53694);
UPDATE `creature_template` SET `scriptname`= 'boss_shannox' WHERE `entry`= 53691;
DELETE FROM `creature_text` WHERE `entry`= 53691;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(53691, 0, 0, 'Yes... I smell them too, Riplimb. Outsiders encroach on the Firelord\'s private grounds. Find their trail, find them for me, that I may dispense punishment', 14, 0, 100, 0, 0, 24584, 'Shannox'),
(53691, 1, 0, 'A-hah Kill them. EAT THEM', 14, 0, 100, 0, 0, 24565, 'Shannox');
UPDATE `creature_template` SET `exp`=3 WHERE  `entry`=24207;
UPDATE `spell_proc_event` SET `procFlags`=1048576, `procEx`=0 WHERE  `entry`=16487;
UPDATE `spell_proc_event` SET `procFlags`=1048576 WHERE  `entry`=16489;
UPDATE `spell_proc_event` SET `procFlags`=1048576, `procEx`=0 WHERE  `entry`=16492;
UPDATE `spell_proc_event` SET `procEx`=0 WHERE  `entry`=16489;
﻿DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_magic_broom','spell_headless_horseman_mount','spell_winged_steed_of_the_ebon_blade','spell_big_love_rocket','spell_invincible','spell_blazing_hippogryph','spell_celestial_steed','spell_x53_touring_rocket');
DELETE FROM `spell_script_names` WHERE `spell_id` = '76838';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (76838, 'spell_warr_strikes_of_opportunity');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (-5217, -80886, 'Tiger\'s Fury -> Remove Primal Madness');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (-5217, -80879, 'Tiger\'s Fury -> Remove Primal Madness');
DELETE FROM `spell_script_names` WHERE  `spell_id`=62606 AND `ScriptName`='spell_dru_savage_defense';
DELETE FROM `spell_script_names` WHERE `spell_id` = '55078';
DELETE FROM `spell_script_names` WHERE `spell_id` = '55095';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (55078, 'spell_dk_blood_plague');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (55095, 'spell_dk_frost_fever');
﻿/*
14:12:20.973 -- aggro
14:12:30.239 -- limb rip 1
14:12:44.685 -- limb rip 2
14:12:35.980 -- face rage 1
14:13:16.026 -- face rage 2 40 secs
14:12:29.023 -- crystal trap throw 1
14:12:55.558 -- crystal trap throw 2
14:12:37.478 -- immolation trap 1
14:12:47.103 -- immolation trap 2
14:12:27.821 -- arcing slash 1
14:12:39.865 -- arcing slash 2
14:12:44.685 -- hurl spear 1
14:13:37.710 -- hurl spear 2
*/
-- Shannox
UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'npc_fl_shannox_trash' WHERE `entry` IN
(53206, 53128, 53095, 53127, 53141, 53134, 53096, 53094, 53732, 53167);
-- Shannox Controller
UPDATE `creature_template` SET `scriptname`= 'npc_fl_shannox_controller' WHERE `entry`= 53910;
DELETE FROM `creature_text` WHERE `entry` = 53910;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(53910, 0, 0, '|TInterface\\Icons\\inv_misc_horn_03.blp:20|tAs the creatures of the Firelands fall, heard the horn of a hunter in the distance.', 41, 0, 100, 0, 0, 6423, 'Shannox Controller'),
(53910, 1, 0, '|TInterface\\Icons\\inv_misc_horn_03.blp:20|tThe hunting horn sounded again, closer and penetrating.', 41, 0, 100, 0, 0, 6423, 'Shannox Controller');
-- Shannox                        rageface / riblimp
DELETE FROM `creature` WHERE `id` IN (53695, 53694);
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `scriptname`= 'boss_shannox' WHERE `entry`= 53691;
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `scriptname`= 'npc_fl_riplimb' WHERE `entry`= 53694;
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `scriptname`= 'npc_fl_rageface' WHERE `entry`= 53695;
DELETE FROM `creature_text` WHERE `entry`= 53691;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(53691, 0, 0, 'Yes... I smell them too, Riplimb. Outsiders encroach on the Firelord\'s private grounds. Find their trail, find them for me, that I may dispense punishment', 14, 0, 100, 0, 0, 24584, 'Shannox'),
(53691, 1, 0, 'A-hah Kill them. EAT THEM', 14, 0, 100, 0, 0, 24565, 'Shannox'),
(53691, 2, 0, 'Now you stay dead', 14, 0, 100, 0, 0, 24579, 'Shannox'),
(53691, 2, 1, 'Dog food', 14, 0, 100, 0, 0, 24578, 'Shannox'),
(53691, 2, 3, 'The Firelord will be most pleased', 14, 0, 100, 0, 0, 24580, 'Shannox to Wadenbeißer'),
(53691, 3, 0, 'Fetch your supper', 14, 0, 100, 0, 0, 24569, 'Shannox'),
(53691, 4, 0, 'Riplimb Oh, you terrible little beasts', 14, 0, 100, 0, 0, 24574, 'Shannox'),
(53691, 5, 0, 'You murderers', 14, 0, 100, 0, 0, 24575, 'Shannox'),
(53691, 6, 0, '%s gets angry when he sees his companions falling', 41, 0, 100, 0, 0, 24574, 'Shannox to Wadenbeißer'),
(53691, 7, 0, 'The pain... Lord of fire, it hurts...', 14, 0, 100, 0, 0, 24568, 'Shannox'),
(53691, 8, 0, 'Go for the throat', 14, 0, 100, 0, 0, 24573, 'Shannox to Augenkratzer'),
(53691, 9, 0, 'Twist in flames, interlopers', 14, 0, 100, 0, 0, 24577, 'Shannox'),
(53691, 9, 1, 'Now you BURN', 14, 0, 100, 0, 0, 24576, 'Shannox');
DELETE FROM `spell_script_names` WHERE `spell_id` IN (100002);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(100002, 'spell_fl_hurl_spear');
UPDATE `creature_template` SET `flags_extra`= 128 WHERE `entry`= 54112;
-- Traps
UPDATE `creature_template` SET `minlevel` = 88, `maxlevel`= 88, `scriptname`= 'npc_fl_immolation_trap' WHERE `entry`= 53724;
UPDATE `creature_template` SET `minlevel` = 88, `maxlevel`= 88, `scriptname`= 'npc_fl_crystal_trap' WHERE `entry`= 53713;
-- Crystal Prison
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'npc_fl_crystal_prison' WHERE `entry`= 53819;
DELETE FROM `spell_script_names` WHERE `spell_id`= 6544;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(6544, 'spell_warr_heroic_leap');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (55233, 'spell_dk_vampiric_blood');
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_dk_will_of_the_necropolis';
DELETE FROM `linked_respawn` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);
UPDATE `creature_template` SET `lootid`= 0 WHERE `entry` IN (1708, 1720, 41096, 40584, 39616, 40577, 40586, 40634, 40765,
40925, 40935, 40936, 40943, 41139, 46641, 46643);
DELETE FROM `spell_proc_event` WHERE `entry` = '84621';
DELETE FROM `spell_proc_event` WHERE `entry` = '84604';
INSERT INTO `spell_proc_event` (`entry`, `procEx`) VALUES (84621, 32);
INSERT INTO `spell_proc_event` (`entry`, `procEx`) VALUES (84604, 32);
UPDATE `spell_proc_event` SET `procEx`=2 WHERE  `entry`=50685;
UPDATE `spell_proc_event` SET `procEx`=2 WHERE  `entry`=50686;
UPDATE `spell_proc_event` SET `procEx`=2 WHERE  `entry`=50687;
DELETE FROM `spell_proc_event` WHERE  `entry`=86627;
UPDATE `creature_template` SET `spell2`='77746' WHERE `entry` IN (2523, 5929, 5950, 15439);
DELETE FROM `spell_script_names` WHERE `spell_id` ='77746';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77746, 'spell_sha_totemic_wrath');
DELETE FROM `spell_script_names` WHERE  `spell_id`=60103 AND `ScriptName`='spell_sha_lava_lash';
DELETE FROM `spell_script_names` WHERE `ScriptName` ='spell_pal_eye_for_an_eye';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (25988, 'spell_pal_eye_for_an_eye');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (9799, 'spell_pal_eye_for_an_eye');
DELETE FROM `spell_script_names` WHERE  `spell_id`=-85117 AND `ScriptName`='spell_pal_divine_purpose';
DELETE FROM `spell_script_names` WHERE  `spell_id`=-87168 AND `ScriptName`='spell_pal_long_arm_of_the_law';
DELETE FROM `spell_proc_event` WHERE  `entry`=85117;
DELETE FROM `spell_proc_event` WHERE  `entry`=86172;
DELETE FROM `spell_script_names` WHERE `spell_id` = '35395';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (35395, 'spell_pal_crusader_strike');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-31884';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (-31884, -57318, 'Avenging Wrath -> Remove Sanctified Wrath');
DELETE FROM `spell_script_names` WHERE  `spell_id`=85285 AND `ScriptName`='spell_pal_sacred_shield';
UPDATE `spell_bonus_data` SET `ap_bonus`=0.102 WHERE  `entry`=53600;
DELETE FROM `spell_proc_event` WHERE `entry` = '84629';
DELETE FROM `spell_proc_event` WHERE `entry` = '84628';
INSERT INTO `spell_proc_event` (`entry`, `procEx`) VALUES (84629, 8208);
INSERT INTO `spell_proc_event` (`entry`, `procEx`) VALUES (84628, 8208);
DELETE FROM `spell_proc_event` WHERE  `entry`=53710;
DELETE FROM `spell_proc_event` WHERE  `entry`=53709;
﻿
/*
12:36:46.857 -- aggro
12:37:06.919 -- asphyxiate 1
12:37:14.158 -- execution delay
12:36:52.442 -- pain and suffering 1
12:37:18.978 -- pain and suffering 2
12:37:00.882 -- wracking pain 1
12:37:27.418 -- wracking pain 2
*/
UPDATE `creature_template` SET `scriptname`= 'boss_baron_ashbury' WHERE `entry`= 46962;
UPDATE `creature_template` SET `flags_extra`= 128 WHERE `entry`= 50604;
DELETE FROM `creature` WHERE `id`= 50604;
DELETE FROM `creature_template_addon` WHERE `entry`= 50604;
DELETE FROM `spell_script_names` WHERE `spell_id`= 93424;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(93424, 'spell_sfk_asphyxiate_damage');
DELETE FROM `creature_text` WHERE `entry`= 46962;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(46962, 1, 0, 'Tally ho', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 2, 0, 'This is just too easy...', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 3, 0, '|TInterface\\Icons\\spell_holy_healingaura.blp:20|tBaron Ashbury begins to channel |cFFFF0000|Hspell:93468|h''Stay of Execution''|h|r ', 41, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 4, 0, 'HA Let\'s at least keep it interesting.', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 5, 0, 'I grow tired of this hunt... Time to die', 14, 0, 100, 0, 0, 0, 'Baron Ashbury'),
(46962, 6, 0, 'Killed by lowly commoners, how droll...', 14, 0, 100, 0, 0, 0, 'Baron Ashbury');
DELETE FROM `conditions` WHERE `SourceEntry`= 93766;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 93766, 0, 0, 31, 0, 3, 50604, 0, 0, 0, '', 'Dark Archangel - Wings Aura');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (93757);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
('93757', '93766', '0', 'Baron Ashbury Wings - Apply Aura'),
('93757', '93812', '0', 'Baron Ashbury - Archangel Damage Aura');
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (48496, 48496, 1);
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (48496, 48499, 2);
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (48496, 48500, 3);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (33891, 5420, 0, 'Tree of Life -> Passive Effect');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-33891, -5420, 0, 'Tree of Life -> Remove Passive Effect');
DELETE FROM `spell_proc_event` WHERE `entry` = '33881';
DELETE FROM `spell_proc_event` WHERE `entry` = '33882';
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (33881, 0, 0, 0, 0, 0, 1048576, 0, 0, 0, 0);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (33882, 0, 0, 0, 0, 0, 1048576, 0, 0, 0, 0);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (45281, 774, 'Nature\'s Ward -> Cast Rejuvenation');
DELETE FROM `spell_proc_event` WHERE  `entry`=61345;
DELETE FROM `spell_proc_event` WHERE  `entry`=61346;
DELETE FROM `spell_proc_event` WHERE  `entry`=16880;
-- Fungal Growth II
SET @ENTRY := 43484;
SET @SOURCETYPE := 0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=@ENTRY;
UPDATE `creature_template` SET `ScriptName`='npc_fungal_growth' WHERE  `entry`=@ENTRY;
-- Fungal Growth II
SET @ENTRY2 := 43497;
SET @SOURCETYPE2 := 0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY2 AND `source_type`=@SOURCETYPE2;
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=@ENTRY2;
UPDATE `creature_template` SET `ScriptName`='npc_fungal_growth' WHERE  `entry`=@ENTRY2;
DELETE FROM `spell_proc_event` WHERE  `entry`=34499;
DELETE FROM `spell_proc_event` WHERE  `entry`=34498;
DELETE FROM `spell_proc_event` WHERE  `entry`=34497;
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (53302, 53302, 1);
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (53302, 53303, 2);
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (53302, 53304, 3);
UPDATE `spell_proc_event` SET `procEx`=0 WHERE  `entry`=53260;
UPDATE `spell_proc_event` SET `procEx`=0 WHERE  `entry`=53259;
UPDATE `spell_proc_event` SET `procEx`=0 WHERE  `entry`=53256;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (94007, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (94006, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
UPDATE `version` SET `db_version`= 'SCDB 02' WHERE `db_version`= 'SCDB 01'
