DELETE FROM `disables` WHERE `sourceType` = '2' AND `entry` IN (631, 603, 616, 650);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(2, 631, 3, '0', '0', 'Icecrown Citadel (Closed)'),
(2, 603, 3, '0', '0', 'Ulduar (Closed)'),
(2, 616, 3, '0', '0', 'The Eye of Eternity (Closed)'),
(2, 650, 3, '0', '0', 'The Eye of Eternity (Closed)');