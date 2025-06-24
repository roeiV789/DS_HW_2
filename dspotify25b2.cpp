// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b2.h"


DSpotify::DSpotify(){

}

DSpotify::~DSpotify() {
}

StatusType DSpotify::addGenre(int genreId){
    if(genreId <=0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if(!GS_UF.addGroup(genreId, genreId)) {
            return StatusType::FAILURE;
        }
        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::addSong(int songId, int genreId){
    if(songId <=0 || genreId <=0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if(!GS_UF.addElement(songId,songId,genreId)) {
            return StatusType::FAILURE;
        }
        return StatusType::SUCCESS;
    }catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::mergeGenres(int genreId1, int genreId2, int genreId3){
    if(genreId1<=0 || genreId2<=0 || genreId3<=0 || genreId1==genreId2 || genreId3==genreId1) {
        return StatusType::INVALID_INPUT;
    }
    try{
        if(!GS_UF.uniteGroups(genreId1, genreId2, genreId3)) {
            return StatusType::FAILURE;
        }
        return StatusType::SUCCESS;
    }catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::getSongGenre(int songId){
    if(songId <=0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        int res = GS_UF.findElementGroup(songId);
        if(res<0) {
            return StatusType::FAILURE;
        }
        return res;
    }catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::getNumberOfSongsByGenre(int genreId){
    if(genreId <=0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        int res = GS_UF.groupSize(genreId);
        if(res<0) {
            return StatusType::FAILURE;
        }
        return res;
    }catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::getNumberOfGenreChanges(int songId){
    if(songId <=0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        int res = GS_UF.getNumberOfGroupChanges(songId);
        if(res<0) {
            return StatusType::FAILURE;
        }
        return res;
    }catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}
