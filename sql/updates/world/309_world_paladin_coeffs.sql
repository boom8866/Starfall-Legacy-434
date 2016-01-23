UPDATE `spell_bonus_data` SET `direct_bonus`=0, `ap_bonus`=0 WHERE `entry`=85673;
DELETE FROM `spell_bonus_data` WHERE `entry` = '20170';
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
(20170, 0, 0, 0, 0, 'Paladin - Seal of Justice');
