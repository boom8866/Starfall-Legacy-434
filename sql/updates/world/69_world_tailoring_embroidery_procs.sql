DELETE FROM `spell_proc_event` WHERE `entry` IN (75171, 75174);
INSERT INTO `spell_proc_event` (`entry`, `Cooldown`) VALUES
(75171, 25, 45);
(75174, 30, 45);