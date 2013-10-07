UPDATE `creature_template` SET `npcflag`=1, `VehicleId`=397, `InhabitType`=4 WHERE  `entry`=41848;

DELETE FROM `waypoints` WHERE `entry` = '41848';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(41848, 1, -5666.14, -1548.64, 423.84, 'Flying Machine WP'),
(41848, 2, -5532.72, -1564.89, 523.81, 'Flying Machine WP'),
(41848, 3, -5015.52, -1679.63, 554.16, 'Flying Machine WP'),
(41848, 4, -4806.97, -1687.68, 549.99, 'Flying Machine WP'),
(41848, 5, -4654.54, -1642.14, 535.58, 'Flying Machine WP'),
(41848, 6, -4556.95, -1645.02, 508.82, 'Flying Machine WP');