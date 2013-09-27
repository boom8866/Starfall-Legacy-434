DELETE FROM `spell_bonus_data` WHERE `entry` =78;
DELETE FROM `spell_script_names` WHERE `spell_id` =78;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
('78', 'spell_warr_heroic_strike');