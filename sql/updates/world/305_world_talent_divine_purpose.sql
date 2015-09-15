DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (85222, 85673, 84963, 85256) AND `spell_effect` = '-90174';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(85222, -90174, 'Light of Dawn -> Remove Divine Purpose'),
(85673, -90174, 'Word of Glory -> Remove Divine Purpose'),
(84963, -90174, 'Inquisition -> Remove Divine Purpose'),
(85256, -90174, 'Templar\'s Verdict -> Remove Divine Purpose');