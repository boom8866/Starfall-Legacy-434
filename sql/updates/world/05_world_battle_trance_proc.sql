-- Battle Trance proc only from Bloodthirst, Mortal Strike and Shield Slam
DELETE FROM `` WHERE `entry` IN(12322, 85741, 85742);
INSERT INTO `spell_proc_event` VALUES
('12322', '0', '0', '33554432', '1536', '0', '4112', '0', '0', '5', '0');
('85741', '0', '0', '33554432', '1536', '0', '4112', '0', '0', '10', '0');
('85742', '0', '0', '33554432', '1536', '0', '4112', '0', '0', '15', '0');
