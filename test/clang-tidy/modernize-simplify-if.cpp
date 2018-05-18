// RUN: %check_clang_tidy %s modernize-simplify-if %t

// FIXME: Add something that triggers the check here.
void f();
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [modernize-simplify-if]

// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}void awesome_f();{{$}}

// FIXME: Add something that doesn't trigger the check here.

bool ret_true() { return true; }
bool ret_false() { return false; }

void awesome_f2()
{
    if(1 < 2)
    {

    }
    bool b = 1 ? true || 5 : true && true;
}
