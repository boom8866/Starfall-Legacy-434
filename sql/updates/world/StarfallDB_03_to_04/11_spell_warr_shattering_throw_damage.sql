DELETE FROM `spell_bonus_data` WHERE `entry` =64382;
DELETE FROM `spell_script_names` WHERE `spell_id` =64382;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
('64382', 'spell_warr_shattering_throw_damage');