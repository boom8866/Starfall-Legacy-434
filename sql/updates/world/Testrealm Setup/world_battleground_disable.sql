DELETE FROM `disables` WHERE `sourceType` = '3' AND `entry` IN (30, 1, 9);
INSERT INTO `disables` (`sourceType`, `entry`, `params_0`, `params_1`, `comment`) VALUES
(3, 30, '0', '0', 'Battleground - Isle of Conquest'),
(3, 1, '0', '0', 'Battleground - Alterac Valley'),
(3, 9, '0', '0', 'Battleground - Strand of the Ancients');
