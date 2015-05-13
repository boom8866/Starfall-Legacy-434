DELETE FROM `spell_group` WHERE `id` = '5013';
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES
(5013, 30808),
(5013, 30802),
(5013, 19506),
(5013, 79101),
(5013, 79102),
(5013, 53646),
(5013, 79057),
(5013, 79058);

DELETE FROM `spell_group_stack_rules` WHERE `group_id` = '5013';
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
(5013, 3);