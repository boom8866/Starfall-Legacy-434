
UPDATE `creature_template` SET `scriptname`= 'npc_fl_molten_orb' WHERE `entry`= 54299;

DELETE FROM `spell_script_names` WHERE spell_id = 101034;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(101034, 'spell_fl_trigger_bridge_cinematic');
