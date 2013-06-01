
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
