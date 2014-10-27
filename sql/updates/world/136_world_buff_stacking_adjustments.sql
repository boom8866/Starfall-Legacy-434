DELETE FROM `spell_group_stack_rules` WHERE `group_id` = '5004';
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
(5004, 3);

DELETE FROM `spell_group` WHERE `spell_id` IN
(79057, 79058, 52109, 53646, 77747) AND `id` = '5004';
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES
(5004, 79057),
(5004, 79058),
(5004, 52109),
(5004, 53646),
(5004, 77747);