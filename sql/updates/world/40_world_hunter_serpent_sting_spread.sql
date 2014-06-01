UPDATE `spell_bonus_data` SET `ap_dot_bonus`=0.0628 WHERE `entry`=1978;

DELETE FROM `spell_bonus_data` WHERE `entry` IN (88466, 88453);
INSERT INTO `spell_bonus_data` (`entry`, `ap_dot_bonus`, `comments`) VALUES
(88466, 0.0628, 'Hunter - Serpent Sting (Spread)'),
(88453, 0.0628, 'Hunter - Serpent Sting (Spread)');