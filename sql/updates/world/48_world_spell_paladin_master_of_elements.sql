DELETE FROM `spell_script_names` WHERE `spell_id` IN (29074, 29075);
INSERT INTO `spell_script_names` VALUES
(29074, 'spell_mage_master_of_elements'),
(29075, 'spell_mage_master_of_elements');

UPDATE `spell_proc_event` SET `SchoolMask`=0 WHERE `entry` IN (29074, 29075, 29076);