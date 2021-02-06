<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class UserEvent extends Model
{
  public $timestamps = false;

  protected $table = "user_event";

  protected $fillable = [
    'user_id',
    'event_id',
    'event_score',
    'datetime'
  ];
}
