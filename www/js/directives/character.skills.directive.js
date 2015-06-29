(function() {
    
    angular.module('sheet')
    .directive('skills', skills);
    
    /////////////////////////////
    
    function skills () {
        return {
            "restrict": "E",
            "controller": skillsCTRL,
            "controllerAs": "skillsVM",
            "scope": {
              "character": "=",
              "editMode": "="
            },
            "bindToController": true,
            "templateUrl": "templates/skills.html"
        }
        
        function skillsCTRL($scope, charactersFactory) {
            var skillsVM = this;
            
            //skillsVM.character = charactersFactory.getCharacterById(skillsVM.characterUid);
            
            skillsVM.skillList = {
                "Acrobatics": {
                    "attribute": "dexterity"
                },
                "Animal Handling": {
                    "attribute": "wisdom"
                },
                "Arcana": {
                    "attribute": "intelligence"
                },
                "Athletics": {
                    "attribute": "strength"
                },
                "Deception": {
                    "attribute": "charisma"
                },
                "History": {
                    "attribute": "intelligence"
                },
                "Insight": {
                    "attribute": "wisdom"
                },
                "Intimidation": {
                    "attribute": "charisma"
                },
                "Investigation": {
                    "attribute": "intelligence"
                },
                "Medicine": {
                    "attribute": "intelligence"
                },
                "Nature": {
                    "attribute": "intelligence"
                },
                "Perception": {
                    "attribute": "wisdom"
                },
                "Performance": {
                    "attribute": "charisma"
                },
                "Persuasion": {
                    "attribute": "charisma"
                },
                "Religion": {
                    "attribute": "intelligence"
                },
                "Sleight of Hand": {
                    "attribute": "dexterity"
                },
                "Stealth": {
                    "attribute": "dexterity"
                },
                "Survival": {
                    "attribute": "wisdom"
                }
            };
            
            //@TODO: Move this into a factory!
            skillsVM.skillsClick = function (skillName) {
                var skillBonus = (skillsVM.character.proficiencies.skills && skillsVM.character.proficiencies.skills[skillName]) ? 2 : 0;
                var statScore = skillsVM.character.stats[skillsVM.skillList[skillName].attribute].score;
                skillBonus = charactersFactory.getModifier(statScore) + skillBonus;
                //roll here
                console.log(skillsVM.character, skillName, skillBonus, statScore);
            }
            
            return skillsVM;
        }
    }
    
})();