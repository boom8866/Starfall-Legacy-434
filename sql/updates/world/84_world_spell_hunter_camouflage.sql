DELETE FROM spell_script_names WHERE `ScriptName` = 'spell_hun_camouflage_ignore' AND `spell_id` IN 
(83254,83244,83243,83242,883,2641,34026,19434,1130,1543,1499,13809,13813,13795,34600,60192,82941,
82939,82945,82948,136,19577,19574,80168,80169,13165,82661,5118,13159,20043);
INSERT INTO `spell_script_names` VALUES
(136, 'spell_hun_camouflage_ignore'),
(83254, 'spell_hun_camouflage_ignore'),
(83244, 'spell_hun_camouflage_ignore'),
(83243, 'spell_hun_camouflage_ignore'),
(83242, 'spell_hun_camouflage_ignore'),
(883, 'spell_hun_camouflage_ignore'),
(2641, 'spell_hun_camouflage_ignore'),
(34026, 'spell_hun_camouflage_ignore'),
(19434, 'spell_hun_camouflage_ignore'),
(1130, 'spell_hun_camouflage_ignore'),
(1543, 'spell_hun_camouflage_ignore'),
(1499, 'spell_hun_camouflage_ignore'),
(13809, 'spell_hun_camouflage_ignore'),
(13813, 'spell_hun_camouflage_ignore'),
(13795, 'spell_hun_camouflage_ignore'),
(34600, 'spell_hun_camouflage_ignore'),
(60192, 'spell_hun_camouflage_ignore'),
(82941, 'spell_hun_camouflage_ignore'),
(82939, 'spell_hun_camouflage_ignore'),
(82945, 'spell_hun_camouflage_ignore'),
(82948, 'spell_hun_camouflage_ignore'),
(19577, 'spell_hun_camouflage_ignore'),
(80168, 'spell_hun_camouflage_ignore'),
(80169, 'spell_hun_camouflage_ignore'),
(13165, 'spell_hun_camouflage_ignore'),
(82661, 'spell_hun_camouflage_ignore'),
(5118, 'spell_hun_camouflage_ignore'),
(13159, 'spell_hun_camouflage_ignore'),
(20043, 'spell_hun_camouflage_ignore');

DELETE FROM spell_script_names WHERE `spell_id` = '94528' AND `ScriptName` = 'spell_hun_flare';
INSERT INTO `spell_script_names` VALUES (94528, 'spell_hun_flare');

DELETE FROM spell_script_names where `spell_id`= '32592' AND `ScriptName` = 'spell_pri_mass_dispel';
INSERT INTO `spell_script_names` VALUES (32592, 'spell_pri_mass_dispel');

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_hun_camouflage';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(80326, 'spell_hun_camouflage');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '51753' AND `spell_effect` = '51755';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-51755' AND `spell_effect` = '-80325';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES 
(51753, 51755,  'Camouflage'),
(-51755, -80325, 'Camouflage Remove');