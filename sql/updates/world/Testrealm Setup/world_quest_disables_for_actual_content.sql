DELETE FROM `disables` WHERE `sourceType` = '1' AND `entry` IN (29157, 29388, 29390, 29156, 29387, 29391);
INSERT INTO `disables` (`sourceType`, `entry`, `comment`) VALUES
(1, 29157, 'Quest: The Zandalari Menace (Content 4.1)'),
(1, 29156, 'Quest: The Troll Incursion (Content 4.1)'),
(1, 29388, 'Quest: Guardians of Hyjal: Firelands Invasion! (Content 4.1)'),
(1, 29387, 'Quest: Guardians of Hyjal: Firelands Invasion! (Content 4.1)'),
(1, 29390, 'Quest: Guardians of Hyjal: Call of the Ancients (Content 4.1)'),
(1, 29391, 'Quest: Guardians of Hyjal: Call of the Ancients (Content 4.1)');