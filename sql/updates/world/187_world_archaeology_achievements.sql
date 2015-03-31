DELETE FROM achievement_criteria_data WHERE criteria_id IN (5315, 5469,5470);
INSERT INTO achievement_criteria_data (criteria_id, type, value1, value2, ScriptName) VALUES (5315, 8, 10, 3, ""), (5469, 8, 50, 3, ""), (5470, 8, 100, 3, "");

DELETE FROM achievement_reward WHERE entry IN (4854, 4855, 4856);
INSERT INTO achievement_reward (entry, title_A, title_H) VALUES (4854, 189, 189), (4855, 190, 190), (4856, 191, 191);
