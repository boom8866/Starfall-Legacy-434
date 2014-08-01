UPDATE `creature_template` SET `difficulty_entry_1`=48902,`minlevel`=87,`maxlevel`=87,`mindmg`=2000,`maxdmg`=2200,`dmg_multiplier`=7.5,`baseattacktime`=1000,`mechanic_immune_mask`=667893759,`faction_A`=14,`faction_H`=14 WHERE `entry` IN (47120, 51350);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (88954,95173,88942,95172);
INSERT INTO `spell_script_names`(`spell_id`, `ScriptName`) VALUES
(88954,'spell_argaloth_consuming_darkness'),
(95173,'spell_argaloth_consuming_darkness'),
(88942,'spell_argaloth_meteor_slash'),
(95172,'spell_argaloth_meteor_slash');
