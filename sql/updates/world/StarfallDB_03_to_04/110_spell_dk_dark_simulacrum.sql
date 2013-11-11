-- Proc records for letting Dark Simulacrum work
DELETE FROM spell_proc_event WHERE entry in(77606, 94984);
INSERT INTO `spell_proc_event` VALUES (77606, 0, 0, 0, 0, 0, 1342264336, 65536, 0, 100, 0);
INSERT INTO `spell_proc_event` VALUES (94984, 0, 0, 0, 0, 0, 1342264336, 65536, 0, 100, 0);

-- Add/Remove check spell when casting copied spell
DELETE FROM spell_linked_spell WHERE spell_trigger in(77616, -77616);
INSERT INTO `spell_linked_spell` VALUES (77616, 94984, 0, 'Dark Simlacrum check spell');
INSERT INTO `spell_linked_spell` VALUES (-77616, -94984, 0, 'Dark Simulacrum remove check spell');