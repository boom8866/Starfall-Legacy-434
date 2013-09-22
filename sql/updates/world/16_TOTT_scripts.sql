-- Lady Naz'jar parts
UPDATE `creature_template` SET `VehicleId`=1338 WHERE `entry`=48571;
UPDATE `creature_template` SET `flags_extra`=129, `unit_flags`='6' WHERE `entry`=40784;

DELETE FROM `spell_script_names` WHERE `spell_id` IN(75690,76307, 91492, 90479);
INSERT INTO `spell_script_names` VALUES
(75690, "spell_tot_waterspout_knockback"),
(76307, "spell_tott_absorb_magic"),
(91492, "spell_tott_absorb_magic"),
(90479, "spell_tot_waterspout_vehicle");

DELETE FROM `disables` WHERE `sourceType`='2' AND `entry`='643';

-- Mindbender Ghur'sha Texts
DELETE FROM `creature_text` WHERE `entry` = 40788;
INSERT INTO `creature_text` VALUES
('40788', '0', '0', 'A new host must be found.', '14', '0', '100', '0', '0', '18860', 'Phase Transition'),
('40788', '1', '0', 'There is only Ghur\'sha.', '14', '0', '100', '0', '0', '18864', 'Mind Control'),
('40788', '1', '1', 'Who are your allies?', '14', '0', '100', '0', '0', '18866', 'Mind Control'),
('40788', '1', '2', 'Give in.', '14', '0', '100', '0', '0', '18865', 'Mind Control'),
('40788', '2', '0', 'Is. This. Reality.', '14', '0', '100', '0', '0', '18867', 'Mind Fog'),
('40788', '3', '0', 'Too weak to serve!', '14', '0', '100', '0', '0', '18861', 'Kill Player'),
('40788', '3', '1', 'Only your memory remains!', '14', '0', '100', '0', '0', '18862', 'Kill Player'),
('40788', '4', '0', 'They are outside the cycle...', '14', '0', '100', '0', '0', '18863', 'Victory');

-- Erunak Stonespeaker
DELETE FROM `creature_text` WHERE `entry` = 40825;
INSERT INTO `creature_text` VALUES
('40825', '0', '0', 'I thank you, my friends. Forgive me. I... I have grown too weak to be of any assistance.', '14', '0', '100', '0', '0', '18662', 'Erunak Stonespeaker'),
('40825', '1', '0', 'I am... weary. You must carry on without me. I shall take my leave once my strength has returned.', '14', '0', '100', '0', '0', '18664', 'Erunak Stonespeaker');