DELETE FROM `spell_script_names` WHERE `spell_id` = '80987';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(80987, 'spell_dh_deepvein_patch_kit');

UPDATE `creature_template` SET `DamageModifier`=2 WHERE `entry` IN (43372, 42918);
UPDATE `creature_template` SET `DamageModifier`=7.5 WHERE `entry`=46441;

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (6287, 6289);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6287, 'at_quest_tod'),
(6289, 'at_quest_tod');