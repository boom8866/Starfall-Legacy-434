DELETE FROM `creature_addon` WHERE `guid` = '129452';
DELETE FROM `creature` WHERE `guid` = '129452';

UPDATE `creature_involvedrelation` SET `id`=25462 WHERE `id`=28357 AND `quest`=12636;
UPDATE `creature_template` SET `InhabitType`=5, `HoverHeight`=4 WHERE `entry`=28511;
UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (28525, 28543, 28542, 28544);
UPDATE `creature` SET `MovementType`=0 WHERE `guid`=128582;
UPDATE `creature_questrelation` SET `id`=28377 WHERE `id`=28658 AND `quest`=12697;
UPDATE `npc_spellclick_spells` SET `npc_entry`=144955 WHERE `npc_entry`=28833 AND `spell_id`=52447;

DELETE FROM `creature_addon` WHERE `guid` IN (770865, 770897, 770908);
DELETE FROM `creature` WHERE `guid` IN (770865, 770897, 770908);

UPDATE `creature` SET `phaseMask` = '1' WHERE id IN
(27928, 28486);

DELETE FROM `creature_questrelation` WHERE `quest` = '12779';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(29110, 12779);

DELETE FROM `creature_involvedrelation` WHERE `quest` = '12779';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(29110, 12779);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-51852';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(-51852, -51890, 0, 'Eye of Acherus Aura Cleanup'),
(-51852, -51892, 0, 'Eye of Acherus Aura Cleanup'),
(-51852, -51923, 0, 'Eye of Acherus Aura Cleanup');

-- Hack fix until we understand why original cannon id (28833) make your client explode
DELETE FROM `creature_template` WHERE `entry` = '144955';
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (144955, 0, 0, 0, 0, 0, 25723, 0, 0, 0, 'Scarlet Cannon', '', 'Gunner', 0, 55, 55, 0, 0, 35, 35, 16777216, 1, 1.14286, 1, 0, 87, 116, 0, 214, 1, 2000, 2000, 2, 0, 2048, 8, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52435, 52576, 0, 0, 52588, 0, 0, 0, 0, 139, 0, 0, '', 0, 3, 1, 10, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 15595);

-- Hack fix until we understand why original cannon id (28887) make your client explode
DELETE FROM `creature_template` WHERE `entry` = '144956';
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (144956, 0, 0, 0, 0, 0, 25723, 0, 0, 0, 'Scarlet Cannon', '', 'Gunner', 0, 55, 55, 0, 0, 35, 35, 16777216, 1, 1.14286, 1, 0, 87, 116, 0, 214, 1, 2000, 2000, 2, 0, 2048, 8, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52435, 52576, 0, 0, 52588, 0, 0, 0, 0, 139, 0, 0, '', 0, 3, 1, 10, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 15595);

UPDATE `creature` SET `id`=144955 WHERE `id`=28833;
UPDATE `creature` SET `id`=144956 WHERE `id`=28887;

DELETE FROM `creature_involvedrelation` WHERE `quest` = '12717';
DELETE FROM `gameobject_involvedrelation` WHERE `quest` = '12717';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(190936, 12717);