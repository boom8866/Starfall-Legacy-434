-- Lady Naz'jar parts
UPDATE `creature_template` SET `VehicleId`=1338 WHERE `entry`=48571;
UPDATE `creature_template` SET `flags_extra`=129, `unit_flags`='6' WHERE `entry`IN(40784,44801);

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

DELETE FROM `creature_template_addon` WHERE `entry` = 44801;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
('44801', '0', '0', '0', '1', '0', '83525');

DELETE FROM `creature_text` WHERE `entry` = 40792;
INSERT INTO `creature_text` VALUES
('40792', '0', '0', 'Ahh - my fearless assistants, I assume.', '14', '0', '100', '0', '0', '19469', 'Neptulon'),
('40792', '1', '0', 'You may yet regret your presence here.', '14', '0', '100', '0', '0', '19470', 'Neptulon'),
('40792', '2', '0', 'As I purify these waters, the servants of filth will surely be stirred. Beware!', '14', '0', '100', '0', '0', '19471', 'Neptulon'),
('40792', '3', '0', 'Patience, guests. The waters are nearly cleansed.', '14', '0', '100', '0', '0', '19475', 'Neptulon'),
('40792', '4', '0', 'The beast has returned! It must not pollute my waters!', '14', '0', '100', '0', '0', '19476', 'Neptulon'),
('40792', '5', '0', 'Augh... Their filthiness stains me!', '14', '0', '100', '0', '0', '19472', 'Neptulon'),
('40792', '6', '0', 'My waters are cleansed! Drink in their power!', '14', '0', '100', '0', '0', '19478', 'Neptulon'),
('40792', '7', '0', 'Behold the power of pure water!', '14', '0', '100', '0', '0', '19477', 'Neptulon'),
('40792', '8', '0', 'Ozumat is vulnerable - kill him now!', '41', '0', '100', '0', '0', '19477', 'Neptulon');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` =76133;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
('76133', '76155', '0', 'Apply Tidal Surge Buff')