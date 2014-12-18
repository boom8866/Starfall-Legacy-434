DELETE FROM `spell_area` WHERE `spell` = '55164' AND `area` IN (616, 4922);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(55164, 616, 0, 0, 8326, 0, 2, 1, 64, 11),
(55164, 4922, 0, 0, 8326, 0, 2, 1, 64, 11);