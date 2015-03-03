DELETE FROM `spell_linked_spell` WHERE  `spell_trigger`=7744 AND `spell_effect`=72757 AND `type`=0;
DELETE FROM `spell_script_names` WHERE `spell_id` = '7744';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(7744, 'spell_racial_will_of_the_forsaken');