<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Group;

class GroupController extends Controller
{
    public function show($group_id){
      $group = Group::where('group_id','=', $group_id)->first();

      return $group;
  }
}
