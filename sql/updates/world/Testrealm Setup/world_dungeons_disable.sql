DELETE FROM `disables` WHERE `sourceType` = '2' AND `entry` IN (36, 754);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(2, 36, 3, '0', '0', 'The Deadmines (4.0) - Close'),
(2, 754, 14, '0', '0', 'Throne of the Four Winds (4.0) - Close');
