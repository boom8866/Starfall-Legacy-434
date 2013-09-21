-- Fix Bloodsurge now should properly proc from Bloodthirst
DELETE FROM `` WHERE `entry` IN(46913, 46914, 46915);
INSERT INTO `spell_proc_event` VALUES
('46913', '0', '4', '0', '1024', '0', '16', '0', '0', '10', '0'),
('46914', '0', '4', '0', '1024', '0', '16', '0', '0', '20', '0'),
('46915', '0', '4', '0', '1024', '0', '16', '0', '0', '30', '0');