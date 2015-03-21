DELETE FROM `spell_proc_event` WHERE `entry` = '53651';
INSERT INTO `spell_proc_event` VALUES
(53651, 2, 10, 3223322624, 0, 279552, 35360, 0, 0, 100, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` = '53651';
INSERT INTO `spell_script_names` VALUES 
(53651, 'spell_pal_lights_beacon');