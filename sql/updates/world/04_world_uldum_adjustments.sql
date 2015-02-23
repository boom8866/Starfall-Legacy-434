UPDATE `gameobject_template` SET `flags`=0 WHERE `entry` IN (205887, 205884, 205889, 205886);

UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid` IN
(181842, 181837, 181834, 181831, 181825, 181803, 181801, 181802);