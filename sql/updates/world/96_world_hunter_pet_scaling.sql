DELETE FROM `spell_bonus_data` WHERE `entry` IN (16827, 17253, 49966);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
(16827, 0, 0, 0, 0, 'Hunter Pet - Claw'),
(17253, 0, 0, 0, 0, 'Hunter Pet - Bite'),
(49966, 0, 0, 0, 0, 'Hunter Pet - Smack');