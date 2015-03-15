UPDATE `spell_bonus_data` SET `direct_bonus`=0.04199 WHERE `entry`=88686;
DELETE FROM `spell_bonus_data` WHERE `entry` = '88684';
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
(88684, 0.486, 0, 0, 0, 'Priest - Holy Word: Serenity');