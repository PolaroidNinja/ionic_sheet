(function() {
    
    angular.module('sheet')
    .controller('characterCTRL', characterCTRL);
    
    /////////////////////////
    
    function characterCTRL ($scope, $stateParams, charactersFactory, classesFactory, $ionicModal, $ionicActionSheet, TEMPLATES) {
        var vm = this;
        
        vm.character = charactersFactory.getCharacterById($stateParams.characterId);
        vm.charClasses = classesFactory.data;
        vm.currentSlide;
       
        vm.editMode = true;
        
        
        $scope.$watch(function() { return vm.editMode; }, function() {
            if(typeof character !== "undefined" && character.combat.hp.current == null) {
                character.combat.hp.current = character.combat.hp.max;
            }
           charactersFactory.saveCharacter(vm.character);
        });
        
        vm.modifier = function(score) {
            var scoreInt = parseInt(score);
            return Math.floor((scoreInt - 10) / 2);
        }
        
        vm.openModal = function(modalType) {
            $ionicModal.fromTemplateUrl(TEMPLATES.MODALS[modalType], {
                scope: $scope,
                animation: 'slide-in-up'
            }).then(function(modal) {
                $scope.modal = modal;
                $scope.modal.show();
            });
        }
        
        vm.addAbility = function(ability) {
            var uid = charactersFactory.generateUID();
            var abilityObj = {
                id: uid,
                name: ability.name,
                description: ability.description,
                order: vm.character.abilities.length || 0
            };
            vm.character.abilities[uid] = abilityObj;
            vm.closeAbilityModal();
        }
        
        vm.closeAbilityModal = function() {
            $scope.modal.hide();
        }
        
        vm.editCard = function(type, uid, editorTemplate) {
            vm.editing = vm.character[type][uid];
            var hideSheet = $ionicActionSheet.show({
                titleText: vm.editing.name,
                cancelText: "Cancel",
                destructiveText: "Delete",
                destructiveButtonClicked: function() {
                    $ionicActionSheet.show({
                        titleText: "Confirm Deleting " + vm.editing.name,
                        destructiveText: "Delete",
                        destructiveButtonClicked: function() {
                            delete vm.character[type][uid];
                            return true;
                        },
                        cancelText: "Cancel"
                    });
                
                    return true;
                },
                buttons: [
                    {text: "Edit"},
                    {text: "Move Up"},
                    {text: "Move Down"},
                ],
                buttonClicked: function(index) {
                    switch(index){
                        case 0: 
                            vm.openModal(editorTemplate);
                            break;
                        case 1: 
                            vm.editing.order = parseInt(vm.editing.order) - 1;
                            break;
                        case 2:
                            vm.editing.order = parseInt(vm.editing.order) + 1;
                            break;
                    }
                    
                    return true;
                }
            });
        }
        
        return vm;
    }
})();