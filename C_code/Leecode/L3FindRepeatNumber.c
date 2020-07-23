/**找出数组中重复的数字
 *在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，
 *但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字
 */
int findRepeatNumber(int* nums, int numsSize)
{
   int j,i;
   for(i=0;i<numsSize;i++)
   {
      for(j=i+1;j<numsSize;j++)
      {
         if(nums[i]==nums[j]);
         printf("%d",nums[i]);
      }
   }
   return nums[i]; 
}