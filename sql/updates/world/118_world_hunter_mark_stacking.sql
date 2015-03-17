DELETE FROM `spell_group_stack_rules` WHERE `group_id` = '5012' AND `stack_rule` = '3';
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
(5012, 3);

DELETE FROM `spell_group` WHERE `id` = '5012' AND `spell_id` IN (88691, 1130, 31615);
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES
(5012, 88691),
(5012, 1130),
(5012, 31615);