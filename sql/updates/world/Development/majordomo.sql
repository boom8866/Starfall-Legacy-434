
/*
15:03:22.321 -- first text
15:03:33.413 -- second text
15:03:44.005 -- 3rd text

15:07:51.001 -- nun gut.


15:13:18.931 -- aggro

15:13:21.536 -- die macht des m. --> skorpion

15:13:21.318 scoprion form



15:13:22.207 -- so every 700 - 800 ms
15:13:23.018
15:13:23.720

15:15:18.927 -- cat form
 
15:15:36.321 -- leaping flames summon 17 secs
15:15:51.999 -- next 16 secs
15:16:04.121 -- next 12 secs


15:15:36.321 -- leaping flames cast
15:15:51.999
*/

DELETE FROM `creature_template_addon` WHERE `entry`= 52571;
UPDATE `creature_template` SET `scriptname`= 'boss_majordomo_staghelm', `dynamicflags`= 0 WHERE `entry`= 52571;

DELETE FROM `creature_text` WHERE `entry`= 52571;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(52571, 0, 0, 'Na, so etwas. Ich bewundere Eure Hartnäckigkeit. Baloroc hat diese Festung tausende von sterblichen Lebzeiten lang bewacht.', 14, 0, 100, 0, 0, 24473, 'Majordomus Hirschhaupt'),
(52571, 1, 0, 'Aber niemand betritt das Heim des Feuerlords!', 14, 0, 100, 0, 0, 24474, 'Majordomus Hirschhaupt'),
(52571, 2, 0, 'Fleht jetzt um Gnade, und vielleicht lasse ich Euch leben. Also, \"Helden\"? Wie lautet Eure Antwort?', 14, 0, 100, 0, 0, 24475, 'Majordomus Hirschhaupt'),
(52571, 3, 0, 'Nun gut. Seht die ungezügelte Macht meines neuen Meisters!', 14, 0, 100, 0, 0, 24464, 'Majordomus Hirschhaupt'),
(52571, 4, 0, 'Die Macht des Meisters kennt viele Formen…', 14, 0, 100, 0, 0, 24483, 'Majordomus Hirschhaupt'),
(52571, 4, 1, 'Seht den Zorn der Feuerlande!', 14, 0, 100, 0, 0, 24485, 'Majordomus Hirschhaupt'),
(52571, 5, 0, '|TInterface\\Icons\\inv_mount_hordescorpiong.blp:20|t%s verwandelt sich in einen |c0087CEFA|Hspell:98379|h[Skorpion]|h|r!', 41, 0, 100, 0, 0, 24483, 'Majordomus Hirschhaupt'),
(52571, 6, 0, '|TInterface\\Icons\\ability_druid_tigersroar.blp:20|t%s verwandelt sich in eine |c0087CEFA|Hspell:98374|h[Katze]|h|r!', 41, 0, 100, 0, 0, 24485, 'Majordomus Hirschhaupt'),
(52571, 7, 0, 'Brennt.', 14, 0, 100, 0, 0, 24477, 'Majordomus Hirschhaupt'),
(52571, 7, 1, 'Bald brennt GANZ Azeroth!', 14, 0, 100, 0, 0, 24479, 'Majordomus Hirschhaupt'),
(52571, 7, 2, 'Ihr habt im Feuer gestanden!', 14, 0, 100, 0, 0, 24481, 'Majordomus Hirschhaupt'),
(52571, 8, 0, 'Nichts als Asche!', 14, 0, 100, 0, 0, 24478, 'Majordomus Hirschhaupt'),
(52571, 9, 0, '|c00FF0000%s beschwört brennende Kugeln!|r', 41, 0, 100, 0, 0, 0, 'Majordomus Hirschhaupt'),
(52571, 10, 0, 'Feuerglanz!', 14, 0, 100, 0, 0, 24472, 'Majordomus Hirschhaupt'),
(52571, 11, 0, '|c00FF0000Sengende Samen beginnen zu wachsen!|r', 41, 0, 100, 0, 0, 24472, 'Majordomus Hirschhaupt'),
(52571, 12, 0, 'Meine Studien… hatten gerade erst begonnen…', 14, 0, 100, 0, 0, 24471, 'Majordomus Hirschhaupt');
