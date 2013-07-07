REPLACE INTO spell_ranks VALUES
(35104, 35104, 1),
(35104, 35110, 2),
(53221, 53221, 1),
(53221, 53222, 2),
(53221, 53224, 3),
(53241, 53241, 1),
(53241, 53243, 2),
(34485, 34485, 1),
(34485, 34486, 2),
(34485, 34487, 3);

REPLACE INTO spell_proc_event VALUES
(53241, 0, 9, 0, 0, 0, 0x100, 0, 0, 100, 0),
(53243, 0, 9, 0, 0, 0, 0x100, 0, 0, 100, 0);

DELETE FROM spell_proc_event WHERE entry IN (53221, 53222, 53224);

REPLACE INTO spell_script_names VALUES
(-34485, "spell_hun_master_marksman"),
(82926, "spell_hun_fire"),
(-35104, "spell_hun_bombardement"),
(-53241, "spell_hun_marked_for_death");