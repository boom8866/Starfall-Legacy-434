DELETE FROM `spell_bonus_data` WHERE `entry` IN (87189, 87188);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
(87189, 0.1010, 0, 0, 0, 'Paladin - Enlightened Judgement r2'),
(87188, 0.2020, 0, 0, 0, 'Paladin - Enlightened Judgement r1');