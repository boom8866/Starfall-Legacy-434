DELETE FROM `spell_group_stack_rules` WHERE `group_id` = '5014';
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
(5014, 3);

DELETE FROM `spell_group` WHERE `id` = '5014';
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES
(5014, 1490),
(5014, 85547),
(5014, 86105),
(5014, 48506),
(5014, 60433),
(5014, 93068);

