<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class User extends Model
{
    public $timestamps = false;

    protected $table = "user";
    protected $fillable = [
      'user_id',
      'group_id',
      'first_name',
      'last_name',
      'member_nr'
    ];

    public function getAverageEventUser(){
      return $this->hasOne("App\Models\AverageEventUser", "user_id", "user_id");
    }

    public function getAverageGroup(){
      return $this->hasOne("App\Models\AverageGroup", "group_id", "group_id");
    }

    public function getAverageUser(){
      return $this->hasOne("App\Models\AverageUser", "user_id", "user_id");
    }

    public function getScore(){
      return $this->hasMany("App\Models\UserEvent", "user_id", "user_id");
    }
}
