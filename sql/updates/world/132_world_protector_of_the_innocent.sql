DELETE FROM `spell_proc_event` WHERE `entry` IN (20138, 20139, 20140);
INSERT INTO `spell_proc_event` (`entry`, `Cooldown`) VALUES
(20138, 1),
(20139, 1),
(20140, 1);