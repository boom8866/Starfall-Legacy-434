-- DUNGEONS
DELETE FROM `disables` WHERE `sourceType` = '2' AND `entry` IN (644, 657, 670, 755, 643, 725, 645, 600);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(2, 644, 2, '0', '0', 'Halls of Originations (Heroic) - Close'),
(2, 657, 2, '0', '0', 'The Vortex Pinnacle (Heroic) - Close'),
(2, 670, 2, '0', '0', 'Grim Batol (Heroic) - Close'),
(2, 755, 2, '0', '0', 'The Lost City of Tol\'Vir (Heroic) - Close'),
(2, 643, 2, '0', '0', 'Throne of the Tides (Heroic) - Close'),
(2, 725, 2, '0', '0', 'The Stonecore (Heroic) - Close'),
(2, 645, 2, '0', '0', 'Blackrock Caverns (Heroic) - Close'),
(2, 600, 2, '0', '0', 'Drak Tharon Keep (Heroic) - Close');

-- RAIDS
DELETE FROM `disables` WHERE `sourceType` = '2' AND `entry` IN (757, 671, 669, 649);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(2, 757, 15, '0', '0', 'Baradin Hold (N/H - 10/25) - Close'),
(2, 671, 15, '0', '0', 'The Bastion of Twilight (N/H - 10/25) - Close'),
(2, 669, 15, '0', '0', 'Blackwing Descent (N/H - 10/25) - Close'),
(2, 649, 15, '0', '0', 'Trial of the Crusader (N/H - 10/25) - Close');

-- OLD DUNGEONS/RAIDS
DELETE FROM `disables` WHERE `sourceType` = '2' AND `entry` IN (650, 616, 603, 631, 533);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(2, 650, 3, '0', '0', 'Trial of the Champion (Normal/Heroic) - Close'),
(2, 616, 3, '0', '0', 'The Eye of Eternity (Closed)'),
(2, 603, 3, '0', '0', 'Ulduar (Closed)'),
(2, 631, 3, '0', '0', 'Icecrown Citadel (Closed)'),
(2, 533, 3, '0', '0', 'Naxxramas (Closed)');